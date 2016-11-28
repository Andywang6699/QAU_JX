/********************************************************
*Name:linux_button_led.c
*Desc: ����LINUX�İ�������LED���򡣵�����KEY1~KEY4ʱ
*�ֱ����LED1~LED4�����һ���Ϩ��
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2012-2-4
*Modify: 2016-4-11
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

//��ʱ����
void delay()
{
	int i;	
	for(i=0;i<70000000;i++);
}

int main(void)
{
	int fd_led,fd_button;
	char down='1';
	
	//��LED�豸
	fd_led = open("/dev/leds", 0);//��LED
	if (fd_led ==-1) 
	{
		perror("open device leds");
		exit(1);
	}
	
	//��key�豸
	fd_button = open("/dev/buttons", 0);//��key
	if (fd_button < 0) 
	{
		perror("open device buttons");
		exit(1);
	}
	
	while(1)
	{
		char current_buttons[8];
		
		if (read(fd_button, current_buttons, sizeof current_buttons) != sizeof current_buttons) 
		{
			perror("read buttons:");
			exit(1);
		}
		
		if(current_buttons[0]==down)//key1����
		{	
			ioctl(fd_led,1,0);//LED1������
			delay();
			ioctl(fd_led,0,0);//LED1Ϩ��
		}
		
		if(current_buttons[1]==down)//key2����
		{		
			ioctl(fd_led,1,1);//LED2������
			delay();
			ioctl(fd_led,0,1);//LED2Ϩ��
		}
			
		if(current_buttons[2]==down)//key3����
		{
			ioctl(fd_led,1,2);//LED3������
			delay();
			ioctl(fd_led,0,2);//LED3Ϩ��
		}
			
		if(current_buttons[3]==down)//key4����
		{
			ioctl(fd_led,1,3);//LED4������
			delay();
			ioctl(fd_led,0,3);//LED4Ϩ��
		}
	}

	close(fd_led);
	close(fd_button);

	return 0;
}
