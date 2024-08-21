#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd, ret;
	char buff[10];

	fd = open("/dev/MyMemory",O_RDWR);
	if (fd < 0)
		perror("File Open fails\n");

	ret = write(fd,"123456",6);
	printf("Write return value : %d\n",ret);

	ret = read(fd,buff,50);
	printf("Read return value: %d buff[0]: %s\n",ret,buff);

	close(fd);
}
