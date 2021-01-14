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

#include "led_opr.h"
#include "led_drv.h"

/* 1. ensure main minor number*/  

static int major=0;
static struct class *led_class;
struct led_operations *p_led_opr;

#define MIN(a,b) (a<b?a:b)

//defined in led_drv.h
void led_class_creat_device(int minor){
	device_create(led_class, NULL, MKDEV(major, minor), NULL, "100ask_led%d", minor); /* /dev/100ask_led0,1,... */
}
void led_class_destroy_device(int minor)
{
	device_destroy(led_class, MKDEV(major, minor));
}
void register_led_operations(struct led_operations *opr)
{
	p_led_opr = opr;
}

//in order to call the three function externally
EXPORT_SYMBOL(led_class_creat_device);
EXPORT_SYMBOL(led_class_destroy_device);
EXPORT_SYMBOL(register_led_operations);

/*corresponding open/read/write function--led*/
static SSIZE_T led_drv_read(struct file *file,char __user *buf,size_t size,loff_t *offset){
	printk("%s %s line %d\n",__FILE__, __FUNCTION__, __LINE__);
	return 0;
}
static SSIZE_T led_drv_write(struct file *file,const char __user *buf,size_t size,loff_t *offset){
	int err;
	char status;
	struct inode *inode =file_inode(file);
	int minor = iminor(inode);
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	err = copy_from_user(&status,buf,1);
	/*ctl led according to the status and minor*/
	p_led_opr->ctl(minor,status);
	return 1;
}
static int led_drv_open(struct inode *node,struct file* file){
	int minor = iminor(node);
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	/*init led according to minor*/
	p_led_opr->init(minor);
	return 0;
}

static int led_drv_close(struct inode *node,struct file *file){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

/*define own's file_operation struct*/
static struct file_operations led_drv = {
	.owner = THIS_MODULE,
	.open = led_drv_open,
	.read = led_drv_read,
	.write = led_drv_write,
	.release = led_drv_close,
};

/*introduce file_operation to kernel-->register driver,init function and exit function 
will call func to register the driver and unstall..*/
//register led driver
static int __init led_init(void){
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	major = register_chrdev(0,"100ask_led",&led_drv);//register file_operation struction
	led_class = class_create(THIS_MODULE,"100ask_led_class");
	err = PTR_ERR(led_class);
	if(IS_ERR(led_class)){
		printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
		unregister_chrdev(major, "led");
		return -1;
		}
	return 0;
}

static void __exit led_exit(void){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);

	class_destroy(led_class);
	unregister_chrdev(major, "100ask_led");
}

/* 7.GPL*/

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
