#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <asm/io.h>
#include "led_opr.h"
#include "leddrv.h"
#include "led_resource.h"

#define CCM_CCGR1_BASE (0X020C406C)
#define SW_MUX_GPIO5_IO03_BASE (0X02290014)
#define GPIO5_DR_BASE (0X020AC000)
#define GPIO5_GDIR_BASE (0X020AC004)

static int g_ledpins[100];
static int g_ledcnt = 0;

static volatile unsigned int *CCM_CCGR1;
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
static volatile unsigned int *GPIO5_GDIR;
static volatile unsigned int *GPIO5_DR;

static int board_demo_led_init (int which){   
	int group = GROUP(g_ledpins[which]);
	int pin = PIN(g_ledpins[which]);
	unsigned int val;
	
	printk("init gpio:group %d,pin %d\n",group,pin);
    if ((5==group)&&(3==pin)) {
        if (!CCM_CCGR1)
        {
            CCM_CCGR1                               = ioremap(0x20C406C, 4);
            IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x2290014, 4);
            GPIO5_GDIR                              = ioremap(0x020AC000 + 0x4, 4);
            GPIO5_DR                                = ioremap(0x020AC000 + 0, 4);
        }
        
        /* GPIO5_IO03 */
        /* a. 使能GPIO5
         * set CCM to enable GPIO5
         * CCM_CCGR1[CG15] 0x20C406C
         * bit[31:30] = 0b11
         */
        *CCM_CCGR1 |= (3<<30);
        
        /* b. 设置GPIO5_IO03用于GPIO
         * set IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3
         *      to configure GPIO5_IO03 as GPIO
         * IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3  0x2290014
         * bit[3:0] = 0b0101 alt5
         */
        val = *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
        val &= ~(0xf);
        val |= (5);
        *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = val;
        
        
        /* b. 设置GPIO5_IO03作为output引脚
         * set GPIO5_GDIR to configure GPIO5_IO03 as output
         * GPIO5_GDIR  0x020AC000 + 0x4
         * bit[3] = 0b1
         */
        *GPIO5_GDIR |= (1<<3);
    	}
    return 0;
}

static int board_demo_led_ctl (int which, char status) {
	int group = GROUP(g_ledpins[which]);
	int pin = PIN(g_ledpins[which]);
	
	printk("set gpio:group %d,pin %d\n",group,pin);
    if ((5==group)&&(3==pin)){
        if (status) /* on: output 0*/
        {
            /* d. 设置GPIO5_DR输出低电平
             * set GPIO5_DR to configure GPIO5_IO03 output 0
             * GPIO5_DR 0x020AC000 + 0
             * bit[3] = 0b0
             */
            *GPIO5_DR &= ~(1<<3);
        }
        else  /* off: output 1*/
        {
            /* e. 设置GPIO5_IO3输出高电平
             * set GPIO5_DR to configure GPIO5_IO03 output 1
             * GPIO5_DR 0x020AC000 + 0
             * bit[3] = 0b1
             */ 
            *GPIO5_DR |= (1<<3);
        }
    }
    return 0;
}

static struct led_operations board_demo_led_opr = {
    .init = board_demo_led_init,
    .ctl  = board_demo_led_ctl,
};

struct led_operations *get_board_led_opr(void)
{
    return &board_demo_led_opr;
};

static int chip_demo_gpio_probe(struct platform_device *pdev)
{
    struct device_node *np;
    int err = 0;
    int led_pin;
	
    np = pdev->dev.of_node;
    if (!np)
        return -1;
	//read the "pin" property of the node 
    err = of_property_read_u32(np, "pin", &led_pin);
    
    g_ledpins[g_ledcnt] = led_pin;
    led_class_create_device(g_ledcnt);
    g_ledcnt++;        
    return 0;
}

static int chip_demo_gpio_remove(struct platform_device *pdev)
{
    int i = 0;
    int err;
    struct device_node *np;
    int led_pin;

    np = pdev->dev.of_node;
    if (!np)
        return -1;

    err = of_property_read_u32(np, "pin", &led_pin);

    for (i = 0; i < g_ledcnt; i++)
    {
        if (g_ledpins[i] == led_pin)
        {
            led_class_destroy_device(i);
            g_ledpins[i] = -1;
            break;
        };
    }

    for (i = 0; i < g_ledcnt; i++)
    {
        if (g_ledpins[i] != -1)
            break;
    }

    if (i == g_ledcnt)
        g_ledcnt = 0;
    
    return 0;
}

static const struct of_device_id ask100_leds[] = {
    { .compatible = "100as,leddrv" },
    { },
};//与设备树的100as,leddrv设备资源相匹配

static struct platform_driver chip_demo_gpio_driver = {
    .probe      = chip_demo_gpio_probe,
    .remove     = chip_demo_gpio_remove,
    .driver     = {
        .name   = "100ask_led",
        .of_match_table = ask100_leds,
    },
};

static int __init chip_demo_gpio_drv_init(void)
{
    int err;
    
    err = platform_driver_register(&chip_demo_gpio_driver); 
    register_led_operations(&board_demo_led_opr);
    
    return 0;
}

static void __exit lchip_demo_gpio_drv_exit(void)
{
    platform_driver_unregister(&chip_demo_gpio_driver);
}

module_init(chip_demo_gpio_drv_init);
module_exit(lchip_demo_gpio_drv_exit);

MODULE_LICENSE("GPL");

