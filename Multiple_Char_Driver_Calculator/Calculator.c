#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A multiple char driver for calculator");
MODULE_AUTHOR("Malik Vindhani");

ssize_t write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t read_sub(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t read_mul(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t read_div(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);

int cal_open(struct inode *inode, struct file *filp);
int cal_release(struct inode *indoe, struct file *filp);

struct file_operations fop =
{
         .owner = THIS_MODULE,
         .open = cal_open,
         .release = cal_release,
};

struct cdev *my_cdev;
 
dev_t MyTestDev,MyDev;

int add_result,sub_result,mul_result,div_result;

int cal_open(struct inode *inode, struct file *filp)
{
	int minor;
	struct file_operations *cal_ptr;

	printk(KERN_INFO "Calculator driver is Open. Run appropriate app file to perform calucaltor operations\n ");
	cal_ptr = filp -> f_op;

	MyTestDev = inode -> i_rdev;
	minor = MINOR(MyTestDev);

	switch(minor)
	{
		case 0:
			cal_ptr -> read = read_add;
			cal_ptr -> write = write_add;
			printk("The File operations selected are : %p & %p\n", cal_ptr,filp);
			break;

		case 1:
                        cal_ptr -> read = read_sub;
                        cal_ptr -> write = write_sub;
                        printk("The File operations selected are : %p & %p\n", cal_ptr->read,cal_ptr->write);
                        break;

                case 2:
                        cal_ptr -> read = read_mul;
                        cal_ptr -> write = write_mul;
                       printk("The File operations selected are : %p & %p\n", cal_ptr->read,cal_ptr->write);
                        break;
        
                case 3:
                        cal_ptr -> read = read_div;
                        cal_ptr -> write = write_div;
                        printk("The File operations selected are : %p & %p\n", cal_ptr->read,cal_ptr->write);
                        break;

		default:
			printk(KERN_ALERT "Wrong input Selected..!!!\n");
			break;

	}

	return 0;	
}

int cal_release(struct inode *indoe, struct file *filp)
{
	printk(KERN_INFO "Calculator driver is closed now....!!!\n ");
	return 0;
}




static int calculator_entry(void)
{
	int result, retval;
	int major, minor;

	printk(KERN_INFO "File = %s, Function = %s, Line = %d\n"__FILE__,__func__,__LINE__);
	printk("Calculator Driver Entry\n");

	result = alloc_chrdev_region(&MyDev,0,4,"Calculator");

	if(result < 0)
	{
		printk(KERN_ALERT "Device registeration is not sucessfull \n");
		retval = result;
	}
	else
	{
		major = MAJOR(MyDev);
		minor = MINOR(MyDev);

		printk("Device is register with Major = %d and Minor = %d\n",major,minor);
		my_cdev = cdev_alloc();
		my_cdev->ops = &fop;

		result = cdev_add(my_cdev,MyDev,4);
		
		if(result < 0)
		{
			printk(KERN_ALERT "Device is not created.\n");

			retval = result;
		}
		else
		{
			retval = 0;
		}
	}	

	return retval;
}

static void calculator_exit(void)
{
	printk(KERN_INFO "File = %s, Function = %s, Line = %d\n"__FILE__,__func__,__LINE__);
	unregister_chrdev_region(MyDev,4);
	cdev_del(my_cdev);
	printk("Device is ungistered sucessfully\n");
}

ssize_t write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuf[80];
	int result;
	int *a = NULL, *b = NULL;
	int retval;

	result = copy_from_user((char *)Kbuf,(char *)Ubuff,count);

	if (result == 0)
	{
		printk("Message from user is %s\n",Kbuf);
		printk("Total data written is %d\n",count);
		retval = count;		
		a = (int*)Kbuf;
		b = (int*)&Kbuf[4];
		
		add_result = *a + *b;
		printk("Final result is %d\n",add_result);		
	}
	else
	{
		printk(KERN_ALERT "Error in writing the data\n");
		retval =  result;
	}

	return retval;
}

ssize_t read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	int result;

	result = copy_to_user((char *)Ubuff,(const char *)&add_result,sizeof(int));

	return result;
}

ssize_t write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[80];
	int result;
	int *a = NULL, *b = NULL;
	int retval;

	result = copy_from_user((char *)Kbuff,(char *)Ubuff,count);

	if(result == 0)
	{
		printk("Message from user space is %s\n",Kbuff);
		printk("Total data written is %d\n",count);
		retval = count;
		a = (int *)Kbuff;
		b = (int *)&Kbuff[4];

		sub_result = (*a) - (*b);
		printk("Result of subtraction is : %d\n",sub_result);
	}
	else
	{
		printk(KERN_ALERT "Error in writting the data. \n");
		retval = result;
	}

	return retval;
}

ssize_t read_sub(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	int result;

	result = copy_to_user(Ubuff,&sub_result,sizeof(sub_result));
	return result;
}

ssize_t write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
        char Kbuff[80];
        int result;
        int *a = NULL, *b = NULL;
        int retval;

        result = copy_from_user((char *)Kbuff,(char *)Ubuff,count);

        if(result == 0)
        {
                printk("Message from user space is %s\n",Kbuff);
                printk("Total data written is %d\n",count);
                retval = count;
                a = (int *)Kbuff;
                b = (int *)&Kbuff[4];

                mul_result = (*a) * (*b);
                printk("Result of multiplication is : %d\n",mul_result);
        }
        else
        {
                printk(KERN_ALERT "Error in writting the data. \n");
                retval = result;
        }

        return retval;
}
 
ssize_t read_mul(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
        int result;

        result = copy_to_user(Ubuff,&mul_result,sizeof(mul_result));
        return result;
}



ssize_t write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
        char Kbuff[80];
        int result;
        int *a = NULL, *b = NULL;
        int retval;
   
        result = copy_from_user((char *)Kbuff,(char *)Ubuff,count);
   
        if(result == 0)
        {
                printk("Message from user space is %s\n",Kbuff);
                printk("Total data written is %d\n",count);
                retval = count;
                a = (int *)Kbuff;
                b = (int *)&Kbuff[4];
   
		if(*b !=0)
		{
                	div_result = *a / *b;
			printk("Result of division is : %d\n",div_result);

		}
		else
		{
			printk(KERN_ALERT "Division with 0 is not possible..!!!\n");
		}
                
        }
        else
        {
                printk(KERN_ALERT "Error in writting the data. \n");
                retval = result;
        }
   
        return retval;
}
   
ssize_t read_div(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
        int result;
   
        result = copy_to_user(Ubuff,&div_result,sizeof(div_result));
        return result;
}
module_init(calculator_entry);
module_exit(calculator_exit);
