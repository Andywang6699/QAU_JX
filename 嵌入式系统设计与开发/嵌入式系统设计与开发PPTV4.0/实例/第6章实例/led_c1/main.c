/********************************************************
*Name: start.S
*Desc: S3C6410����������LED�ƣ�ʹ��C���Ե��
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2014-6-4
*Modify: 2016-4-11
*********************************************************/

// ��ʱ
void delay()
{
	volatile int i = 0x500000;
	while (i--);
}

int main()
{
	// ��������
	volatile unsigned long *gpkcon0 = (volatile unsigned long *)0x7F008800;
	volatile unsigned long *gpkdat = (volatile unsigned long *)0x7F008808;
	
	*gpkcon0 = 0x11110000;	//����GPK4/5/6/7Ϊ�������

	// �����
	while (1)
	{
        *gpkdat=0x000000f0;    //GPKDAT=0x000000f0,GPKDAT[7:4]=1111,4��LEDȫ��
        delay();
        *gpkdat=0x000000e0;    //GPKDAT=0x000000e0,GPKDAT[7:4]=1110,LED1����
        delay();
        *gpkdat=0x000000d0;    //GPKDAT=0x000000d0,GPKDAT[7:4]=1101,LED2����
        delay();
        *gpkdat=0x000000b0;    //GPKDAT=0x000000b0,GPKDAT[7:4]=1011,LED3����
 	delay();
        *gpkdat=0x00000070;    //GPKDAT=0x00000070,GPKDAT[7:4]=0111,LED4����
       delay();
        *gpkdat=0x00000000;    //GPKDAT=0x00000000,GPKDAT[7:4]=0000,4��LEDȫ��
	delay();
	}
	
	return 0;
}

