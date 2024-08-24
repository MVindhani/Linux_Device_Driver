#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<asm/ioctl.h>
#include<stdlib.h>
#include "ioctl.h"

#define BAUD_RATE 9000
#define BIT_SET 8

int main()
{
	int fd,result;;
	char Ubuff[] = "This is user buffer from ioctl app. \n";
	char Kbuff[80];

	fd = open("/dev/ioctl",O_RDWR,0777);

	if(fd < 0)
	{
		perror("Not able to open the device...!!\n");
		return -1;
	}
	else
	{
		read(fd,Kbuff,sizeof(Kbuff));
		write(fd,&Ubuff,sizeof(Ubuff));
		ioctl(fd,SET_BAUD_RATE,BAUD_RATE);
		ioctl(fd,SET_STOP_BIT,BIT_SET);
		ioctl(fd,SET_DIRECTION,NULL);
	}

	close(fd);

	return 0;
}
