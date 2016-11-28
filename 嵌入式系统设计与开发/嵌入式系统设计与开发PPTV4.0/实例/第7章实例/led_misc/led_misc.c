/********************************************************
*Name:led_misc.c
*Desc: LED�����豸(misc)���������Զ��������豸�ţ��Զ������豸�ڵ�
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

#define DEVICE_NAME "myled_misc"

//volatile unsigned long *gpkcon0=NULL;
//volatile unsigned long *gpkdat=NULL;

static int led_misc_open(struct inode *inode, 
							struct file *file)
{
	//printk("led_misc_open\n");
	//����GPK4/5/6/7Ϊ�������
	unsigned tmp;
	
	tmp = readl(S3C64XX_GPKCON);//��GPKCON0�Ĵ�����ֵ	
	
	tmp &=  ~(0xffffU<<16);//����
	tmp |= (0x1<<(4*4)) |(0x1<<(5*4))|(0x1<<(6*4))|(0x1<<(7*4));//����Ϊ���
	
	writel(tmp, S3C64XX_GPKCON);//д��GPKCON0�Ĵ���
	
	//*gpkcon0  &=  ~(0xffff<<16);//GPKCON0[31:16]����
	//*gpkcon0 |=  (0x1<<(4*4)) |(0x1<<(5*4))|(0x1<<(6*4))|(0x1<<(7*4));
		//����GPK4/5/6/7Ϊ�������
	return 0;	
}

static long led_misc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch(cmd) {
    unsigned int tmp;
    case 0:
    case 1:
    	if(arg > 4) return -EINVAL;
			tmp = readl(S3C64XX_GPKDAT);		//read GPK io data
			tmp &= ~(1 << (4 + arg));		//clear bit
      tmp |=  ((!cmd) << (4 + arg));		//set bit with cmd
      writel(tmp, S3C64XX_GPKDAT);		//write data register
      return 0;
    default:
        return -EINVAL;
    }
}

static struct file_operations led_misc_fops = {
    .owner = THIS_MODULE,
    .open = led_misc_open,
    .unlocked_ioctl = led_misc_ioctl,
    //linux 2.6�ں���iotcl����ԭ��Ϊ:
    //long (* unlocked_ioctl)(struct *file,unsigned int,unsigned long)
    //��2.4�ں��еĲ�ͬ 
};

/*misc device�������豸�������豸��Ϊ10�������ַ��豸*/
static struct miscdevice led_misc_misc = {  
    //���豸�ţ�ע�ⲻҪ��/proc/misc�����������豸���豸�ų�ͻ
    .minor = MISC_DYNAMIC_MINOR,	//MISC_DYNAMIC_MINOR����̬��ȡ���豸��
    .name = DEVICE_NAME,		//�豸����,��������/dev/myled_misc�豸�ڵ�
    .fops = &led_misc_fops,
};


int led_misc_init(void)
{
	//gpkcon0=(volatile unsigned long *)ioremap(0x7F008800,16);//ioremap��1������Ϊ��ʼ��ַ����2������Ϊ���ȣ�
	//gpkdat=gpkcon0+2;//�����2ʵ�����Ǽ�2��long�ͱ������ȣ���8���ֽ�
	/* �ú������Զ������豸�ڵ㣬���豸�ļ� */
	misc_register(&led_misc_misc);
	printk (DEVICE_NAME"\tinitialized\n");
	
	return 0;
}

void led_misc_exit(void)
{
    misc_deregister(&led_misc_misc);
}

module_init(led_misc_init);
module_exit(led_misc_exit);


MODULE_AUTHOR("YHD");//��������������
MODULE_DESCRIPTION("THE LED_MISC DRIVER");//������Ϣ
MODULE_LICENSE("GPL");//��ѭ��Э��