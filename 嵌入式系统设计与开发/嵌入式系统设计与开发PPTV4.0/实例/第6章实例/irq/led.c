/********************************************************
*Name: led.c
*Desc: S3C6410����жϳ����LED��غ���
*Author: yoyoba(stuyou@126.com)
*Date: 2014-6-7
*Modify: 2016-4-8
*********************************************************/

#include "irq.h"

void delay()
{
	volatile int i = 0x500000;
	while (i--);
}


//LED��ʼ������������GPK4~7Ϊ�������
void led_init()
{
	GPKCON0=(GPKCON0&~(0xffffU<<16))
			|GPK4_OUT
			|GPK5_OUT
			|GPK6_OUT
			|GPK7_OUT;
}

//LED����������ͨ��state����������LED������Ϩ��
void led_display(int state)
{
	GPKDAT=(GPKDAT&~(0xf<<4))|((state&0xf)<<4);
}

