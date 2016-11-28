/********************************************************
*Name:linux_led.c
*Desc: ����LINUX��LED���򣬳������к����ε���LED1~LED4
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2014-2-4
*Modify: 2016-4-11
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//��ʱ����
void delay()
{
	int i;	
	for(i=0;i<70000000;i++);
}

int main()
{
	int fd;

	fd = open("/dev/leds", 0);//��LED�豸�������ļ�������
	if (fd ==-1) 
	{
		perror("open device leds");
		exit(1);
	}
	
	fprintf(stdout,"fd=%d\n",fd);	//���LED�ļ�������
	
	while(1)
	{
		/*ioctl(fd, on, led_no)��������������LED�ơ�
		on=1������LED��on=0��Ϩ��LED��
		led_noȡֵΪ0��1��2��3��
		�ֱ����LED1��LED2��LED3��LED4*/
		ioctl(fd,1,0);//LED1����
		fprintf(stdout,"LED 1 ON\n"); 
		delay();
		ioctl(fd,0,0);//LED1Ϩ��
		fprintf(stdout,"LED 1 OFF\n");
		delay();

		ioctl(fd,1,1); //LED2����
		fprintf(stdout,"LED 2 ON\n");
		delay();
		ioctl(fd,0,1); //LED2Ϩ��
		fprintf(stdout,"LED 2 OFF\n");
		delay();

		ioctl(fd,1,2); //LED3����
		fprintf(stdout,"LED 3 ON\n");
		delay();
		ioctl(fd,0,2); //LED1Ϩ��
		fprintf(stdout,"LED 3 OFF\n");
		delay();

		ioctl(fd,1,3); //LED4����
		fprintf(stdout,"LED 4 ON\n");
		delay();
		ioctl(fd,0,3); //LED1Ϩ��
		fprintf(stdout,"LED 4 OFF\n");
		delay();
	}
	close(fd);
	return 0;
}
