/********************************************************
*Name:first_drv_test.c
*Desc: ��1����������Ĳ��Գ���
*��������֮��tiny6410������
*Author: yoyoba(stuyou@126.com)
*Date: 2016-2-4
*Modify: 2016-4-11
*********************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	int val = 1;
	
	fd = open("/dev/myfirst_drv", O_RDWR);
	
	if (fd < 0)
	{
		printf("can't open!\n");
	}
	
	write(fd, &val, 4);
	
	return 0;
}

