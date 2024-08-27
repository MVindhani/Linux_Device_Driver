#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
    int fd,len;
    char Ubuff = "This is User Space buffer.\n";

    fd = open("/dev/sleppy_device",fd,O_RDWR);

    len = read(fd,Ubuff,sizeof(Ubuff));
    printf("Data read is of %ld bites \n",len);

    len = write(fd,Ubuff,sizeof(Ubuff));
    printf("Data written is of %ls bites \n",len);
    return 0;
}