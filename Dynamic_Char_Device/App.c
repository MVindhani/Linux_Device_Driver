#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd;

    char user_buf[] = "Hello from USer Buffer";

    fd = open("/dev/DynamicCharDriver",O_RDWR,0777);
    if(fd < 0)
    {
        perror("Open fails..!!\n");
    }
    
    write(fd,user_buf,sizeof(user_buf));
    
    close(fd);
    
    return 0;
}