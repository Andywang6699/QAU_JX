/********************************************************
*Name: irq.c
*Desc: S3C6410����жϳ�����ж���غ���
*Author: yoyoba(stuyou@126.com)
*Date: 2014-6-7
*Modify: 2016-4-10
*********************************************************/

#include "irq.h"

extern unsigned long do_irq;

//�����������
void key_isr(void)
{
	unsigned long key_press=0;
	key_press=(EINT0PEND & 0xf);//��EINT0PEND[3:0]���ж��ĸ�������

	switch(key_press)
	{	//key1����
		case 1:
		{
			led_display(LED_ALL_OFF);
			led_display(LED1_ON);
			break;
		}
		//key2����
		case 2:
		{
			led_display(LED_ALL_OFF);
			led_display(LED2_ON);
			break;
		}
		//key3����
		case 4:
		{
			led_display(LED_ALL_OFF);
			led_display(LED3_ON);
			break;
		}
		//key4����
		case 8:
		{
			led_display(LED_ALL_OFF);
			led_display(LED4_ON);
			break;
		}

		default:
			break;

	}
	
	//���ж�
	EINT0PEND   = 0xf;
	VIC0ADDRESS = 0;
}

//�жϳ�ʼ�������������ж�Դ��ʼ�����жϿ�������ʼ��
void irq_init(void)
{
	//�ж�Դ��ʼ����ʼ
	/* ����GPN0~3����Ϊ�жϹ��� */
	GPNCON &= ~(0xff);
	GPNCON |= 0xaa;

	/* �����жϴ�����ʽΪ: �½��ش��� */
	EINT0CON0 &= ~(0xff);
	EINT0CON0 |= 0x22;

	/* �����ж� */
	EINT0MASK &= ~(0xf);
	//�ж�Դ��ʼ������

	//�жϿ�������ʼ����ʼ
	VIC0INTENCLEAR |= (0x1);//�жϿ������ر��ж�
	VIC0INTSELECT &= (~(0x1));//�趨0���ж�Դ���ж�����ΪIRQ
	VIC0ADDRESS = 0;//���ж�
	
	//�жϷ�������ڵ�ַ��ֵ��VIC0VECTADDR0
	//�жϷ���ʱ��CPU���Զ���VIC0VECTADDR0��ȡ
	//�жϷ���������ڵ�ַ��ִ���жϷ�����
	//����VIC_PORTʹ��ģʽ�£��жϷ����������
	//�쳣����������ʹ��sys_busģʽ�����ж�
	VIC0VECTADDR0 = (unsigned long)&do_irq;
	
	/* ���жϿ�������ʹ����Щ�ж� */
	VIC0INTENABLE |= (0x1); /* bit0: EINT0~3 */
	//�жϿ�������ʼ������
}		


/*void do_irq(void)
{
	//�˶δ�����sys_busģʽ�µ��жϴ���ʽ
	//���ַ�ʽ��tiny6410��ò�Ƶ��Բ�ͨ
	void (*the_isr)(void);

	the_isr = VIC0ADDRESS;

	the_isr();

	EINT0PEND   = 0xf;
	VIC0ADDRESS = 0;
} */


