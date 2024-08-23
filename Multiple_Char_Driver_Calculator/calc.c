#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

struct data
{
	int a;
	int b;
};

struct data my_data;
int main()
{
	int fd;
	int result;
	int choice;

	my_data.a = 10;
	my_data.b = 6;

	printf("Enter \n1. Add\n2. Sub\n3. Mul\n4. Div\n");
	printf("Enter your choice : ");
	scanf("%d",&choice);

	printf("Enter 2 numbers : ");
	scanf("%d %d",&my_data.a,&my_data.b);

	switch(choice)
	{
	
	case 1:

		fd = open("/dev/add",O_RDWR,0777);
		if (fd < 0)
		{
			perror("Device cannot be opened\n");
			return -1;
		}
		else
		{
			if( write(fd,&my_data,sizeof(struct data)) < 0 )
			{
				perror("Write cannot be performed\n");
				return -1;
			}
			sleep(2);	
			if( read(fd,&result,sizeof(result)) < 0 )
			{
				perror("Read cannot be performed\n");
				return -1;
			}
		
			printf("Addition is %d\n",result);
			close(fd);
		}
		break;
        case 2:
        
                 fd = open("/dev/sub",O_RDWR,0777);
                 if (fd < 0)
                 {
                         perror("Device cannot be opened\n");
                         return -1;
                 }
                 else
                 {
                         if( write(fd,&my_data,sizeof(struct data)) < 0 )
                         {
                                 perror("Write cannot be performed\n");
                                 return -1;
                         }
                         sleep(2);
                         if( read(fd,&result,sizeof(result)) < 0 )
                         {
                                 perror("Read cannot be performed\n");
                                 return -1;
                         }
 
                         printf("Subtraction is %d\n",result);
                         close(fd);
                 }
                 break;
        case 3:
 
                  fd = open("/dev/mul",O_RDWR,0777);
                  if (fd < 0)
                  {
                          perror("Device cannot be opened\n");
                          return -1;
                  }
                  else
                  {
                          if( write(fd,&my_data,sizeof(struct data)) < 0 )
                          {
                                  perror("Write cannot be performed\n");
                                  return -1;
                          }
                          sleep(2);
                          if( read(fd,&result,sizeof(result)) < 0 )
                          {
                                  perror("Read cannot be performed\n");
                                  return -1;
                          }
 
                          printf("multiplication is %d\n",result);
                          close(fd);
                  }
                  break;
        case 4:

                  fd = open("/dev/div",O_RDWR,0777);
                  if (fd < 0)
                  {
                         perror("Device cannot be opened\n");
                         return -1;
                  }
                  else
                  {
			if(my_data.b !=0)
			{
                        	if( write(fd,&my_data,sizeof(struct data)) < 0 )
                         	{
                                	 perror("Write cannot be performed\n");
                                 	return -1;
                         	}
                         	sleep(2);
                       		if( read(fd,&result,sizeof(result)) < 0 )
                       		{
                       		        perror("Read cannot be performed\n");
                       		        return -1;
                        	}

                   	        printf("Division is %d\n",result);
                         	close(fd);
			}
			else
			{
				printf("Divide by 0 not possible\n");
			}
                 }
                 break;
	
	default:
		printf("Wrong Choice..!!!\n");
		break;
	}
	return 0;
}
	
