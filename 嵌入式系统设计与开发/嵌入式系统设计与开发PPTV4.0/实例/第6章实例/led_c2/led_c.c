/********************************************************
*Name: main.c
*Desc: S3C6410����������LED�ƣ�ʹ��C���ԡ�LED��غ���
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2014-5-2
*Modify: 2016-4-11
*********************************************************/

#include "led.h"

// ��ʱ����
void delay()
{
	volatile int i = 0x500000;
	while (i--);
}

//LED����������ͨ��state����������LED������Ϩ��
void led_display(int state)
{
	GPKDAT=(GPKDAT&~(0xf<<4))|((state&0xf)<<4);
}

