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

#include "led_resource.h"


static struct resource resources[] = {
        {
                .start = GROUP_PIN(3,1),
                .flags = IORESOURCE_IRQ,
        },
        {
                .start = GROUP_PIN(5,8),
                .flags = IORESOURCE_IRQ,
        },
};


static struct platform_device board_A_led_dev  = {
	.name = "100ask_led",
	.num_resources = ARRAY_SIZE(resources),
	.resource = resources,
};

static int led_dev_init(void)
{
	int err;
	
	err = platform_device_register(&board_A_led_dev);
	
	return 0;
}

static void led_dev_exit(void)
{
	platform_device_unregister(&board_A_led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");

