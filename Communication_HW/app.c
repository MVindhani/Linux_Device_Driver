#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    unsigned char byte,dummy;
    
    FILE* PARALLELPORT;

    PARALLELPORT = fopen("/dev/Parallel_port_IO","w");
    setvbuf(PARALLELPORT,&dummy,_IONBF,1);

    byte = 1;

    while(1)
    {

        printf("Byte value is %d\n",byte);
        fwrite(&byte,1,1,PARALLELPORT);
        sleep(1);

        byte<<=1;

        if(byte == 0)
            byte = 1;
    }

    fclose(PARALLELPORT);
    

    return 0;
}