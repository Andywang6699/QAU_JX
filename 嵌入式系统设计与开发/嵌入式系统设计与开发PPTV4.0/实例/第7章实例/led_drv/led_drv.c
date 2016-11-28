/********************************************************
*Name:led_drv.c
*Desc: LED���������Զ��������豸�ţ��Զ������豸�ڵ�
*��������֮��tiny6410������
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

static struct class *led_drv_class;
//static struct class_device	*first_drv_class_dev;

volatile unsigned long *gpkcon0=NULL;
volatile unsigned long *gpkdat=NULL;

static int led_drv_open(struct inode *inode,
                                             struct file *file)
{
	//printk("led_drv_open\n");
	//����GPK4/5/6/7Ϊ�������
	*gpkcon0  &=  ~(0xffff<<16);//GPKCON0[31:16]����
	*gpkcon0 |=  (0x1<<(4*4)) |(0x1<<(5*4))|(0x1<<(6*4))|(0x1<<(7*4));
		//����GPK4/5/6/7Ϊ�������
	return 0;	
}

static ssize_t led_drv_write(struct file *file, 
	                                           const char __user *buf, 
	                                           size_t count, 
	                                           loff_t * ppos)
{
	//printk("led_drv_write\n");
	int val;
	copy_from_user(&val, buf, count);//�û��ռ䵽�ں˿ռ䴫������
	if(val==1)
		{
		//LED1~LED4ȫ��
		*gpkdat &= ~(0xf<<4);//GPKDAT[0:4]����
		*gpkdat |= (0x0<<4);//����͵�ƽ��LED����
		}
	else if(val == 0)
		{
		//LED1~LED4ȫ��
		*gpkdat &= ~(0xf<<4);//GPKDAT[0:4]����
		*gpkdat |= (0xf<<4);//����ߵ�ƽ��LEDϨ��
		}
	
	return 0;
}

static struct file_operations led_drv_fops = {
    	.owner  =   THIS_MODULE,    
/* ����һ���꣬�������ģ��ʱ�Զ�������__this_module���� */
    	.open   =   led_drv_open,     
	.write   =	  led_drv_write,	   
}; 

int major;
int led_drv_init(void)
{
 	major=register_chrdev(0, "leddrv", &led_drv_fops);

	led_drv_class = class_create(THIS_MODULE, "led_drv");
	 device_create(led_drv_class, NULL, MKDEV(major, 0), NULL, "myled_drv");
	//�����豸�ڵ�:/dev/myled_drv�����豸��Ϊmajor�����豸��Ϊ0
	gpkcon0=(volatile unsigned long *)ioremap(0x7F008800,16);//ioremap��1������Ϊ��ʼ��ַ����2������Ϊ���ȣ�
	gpkdat=gpkcon0+2;//�����2ʵ�����Ǽ�2��long�ͱ������ȣ���8���ֽ�
	
	
	return 0;
}

void led_drv_exit(void)
{
 	unregister_chrdev(major, "leddrv");

	//class_device_unregister(first_drv_class_dev);
	device_destroy(led_drv_class,MKDEV(major, 0));
	class_destroy(led_drv_class);

	iounmap(gpkcon0);
}

module_init(led_drv_init);
module_exit(led_drv_exit);

MODULE_AUTHOR("YHD");//��������������
MODULE_DESCRIPTION("THE LED DRIVER");//������Ϣ
MODULE_LICENSE("GPL");//��ѭ��Э��

