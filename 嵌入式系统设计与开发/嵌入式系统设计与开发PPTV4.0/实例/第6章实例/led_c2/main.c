/********************************************************
*Name: main.c
*Desc: S3C6410����������LED�ƣ�ʹ��C���������������
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2014-5-2
*Modify: 2016-4-11
*********************************************************/
#include "led.h"

int main()
{
	GPKCON0=(GPKCON0&~(0xFFFFU<<16))|GPK4_OUT|GPK5_OUT|GPK6_OUT|GPK7_OUT;
	//����GPKCON0�Ĵ�����ʹ��GPK4~7Ϊ����˿ڣ�ͬʱGPKCON0������λ���ֲ���
	// �����
	while (1)
	{
		led_display(LED_ALL_OFF);
		delay();
		led_display(LED1_ON);
		delay();
		led_display(LED2_ON);
		delay();
		led_display(LED3_ON);
		delay();
		led_display(LED4_ON);
		delay();
		led_display(LED_ALL_ON);
		delay();
	}
	
	return 0;
}

