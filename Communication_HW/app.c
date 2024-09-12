#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    unsigned char byte,dummy;
    
    FILE* PARALLELPORT;

    PARALLELPORT = fopen("/dev/Parallel_port_IO","w"); /* The fopen() function shall open the file whose pathname is the string pointed to by filename, and associates a stream with it.*/

    /*
    int setvbuf( FILE *fp, char *buf, int mode, size_t size );
        fp    : The stream that you want to associate with a buffer.
        buf   : NULL, or a pointer to the buffer.
        mode  : How you want the stream to be buffered:
                _IOFBF — input and output are fully buffered.
                _IOLBF — output is line-buffered; that is, the buffer is flushed when a newline character is written, when the buffer is full, or when input is requested 
                _IONBF — input and output are completely unbuffered.
        size  : The size of the buffer.  

        Description : The setvbuf() function associates a buffer with the stream designated by fp.
                      If you want to call setvbuf(), you must call it after opening the stream, but before doing any reading, writing, or seeking.
                      If buf isn't NULL, the buffer it points to is used instead of an automatically allocated buffer.
    */

    setvbuf(PARALLELPORT,&dummy,_IONBF,1);

    byte = 1;

    while(1)
    {

        printf("Byte value is %d\n",byte);
        fwrite(&byte,1,1,PARALLELPORT);

        /*
            size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);

            Description : The fwrite() function shall write, from the array pointed to by ptr, up to nitems elements whose size is specified by size, to
                          the stream pointed to by stream.     
        */
        sleep(1);

        byte<<=1;

        if(byte == 0)
            byte = 1;
    }

    fclose(PARALLELPORT);
    

    return 0;
}