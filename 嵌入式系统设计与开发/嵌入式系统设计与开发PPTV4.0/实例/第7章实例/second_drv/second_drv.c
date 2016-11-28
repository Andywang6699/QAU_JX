/********************************************************
*Name:second_drv.c
*Desc: 第2个驱动程序，自动分配主设备号，自动创建设备节点
*基于友善之臂tiny6410开发板
*Author: yoyoba(stuyou@126.com)
*Date: 2016-2-4
*Modify: 2016-4-11
*********************************************************/
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
//#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-e.h>
#include <mach/gpio-bank-k.h>
#include <linux/device.h>

static struct class *second_drv_class;
//static struct class_device	*first_drv_class_dev;

static int second_drv_open(struct inode *inode,
                                             struct file *file)
{
	printk("second_drv_open\n");
	return 0;	
}

static ssize_t second_drv_write(struct file *file, 
	                                           const char __user *buf, 
	                                           size_t count, 
	                                           loff_t * ppos)
{
	printk("second_drv_write\n");
	return 0;
}

static struct file_operations second_drv_fops = {
    	.owner  =   THIS_MODULE,    
/* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    	.open   =   second_drv_open,     
	.write   =	  second_drv_write,	   
}; 

int major;
int second_drv_init(void)
{
 	major=register_chrdev(0, "seconddrv", &second_drv_fops);

	second_drv_class = class_create(THIS_MODULE, "second_drv");

	//first_drv_class_dev = class_device_create(first_drv_class, NULL, MKDEV(major, 0), NULL, "mysecond_drv");
	 device_create(second_drv_class, NULL, MKDEV(major, 0), NULL, "mysecond_drv");
	//创建设备节点:/dev/mysecond_drv，主设备号为major，次设备号为0
	
	return 0;
}

void second_drv_exit(void)
{
 	unregister_chrdev(major, "seconddrv");

	//class_device_unregister(first_drv_class_dev);
	device_destroy(second_drv_class,MKDEV(major, 0));	//注销设备节点
	class_destroy(second_drv_class);
}

module_init(second_drv_init);
module_exit(second_drv_exit);

MODULE_AUTHOR("YHD");//驱动程序所有者
MODULE_DESCRIPTION("THE SECOND DRIVER");//描述信息
MODULE_LICENSE("GPL");//遵循的协议

