#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include "ioctl.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to demostrate working of ioctl, without HW.");
MODULE_AUTHOR("Malik Vindhani");

dev_t MyDev;
struct cdev *my_cdev;

int ioctl_open(struct inode *inode, struct file *filp);
int ioctl_release(struct inode *indoe, struct file *filp);
ssize_t ioctl_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t ioctl_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
long ioctl_ioctl (struct file * filp, unsigned int cmd, unsigned long arg);


struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read = ioctl_read,
	.write = ioctl_write,
	.open = ioctl_open,
	.release = ioctl_release,
	.unlocked_ioctl = ioctl_ioctl,
};

int ioctl_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Device is open\n");
	return 0;
}

int ioctl_release(struct inode *indoe, struct file *filp)
{
	printk(KERN_INFO "Device is closed\n");
	return 0;
}

ssize_t ioctl_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char kbuff[80];
	int result;

	printk("Write method invocked...!! \n");

	result = copy_from_user((char *)kbuff,(char *)Ubuff,count);
	
	if (result == 0)
	{
		printk("Message from user is %s\n",kbuff);
		printk("Data written is %d\n",count);

		return count;
	}
	else
	{
		printk(KERN_ALERT "Writting is not sucessfull.\n");
		return result;
	}	
}

ssize_t ioctl_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	int result;
	char kbuff[] = "Data from kernel to user...";
	printk("Read method invocked...!!!\n");
	result = copy_to_user((char *)Ubuff,(char *)kbuff,sizeof(kbuff));
	
	if(result == 0)
	{
		printk("Data sucessfully read..!!\n");
		return result;
	}
	else
	{
		printk(KERN_ALERT "Data is not read sucessfully.\n");
		return result;
	}
}

long ioctl_ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "IOCTL function called in kernel..!!\n");
	switch(cmd)
	{
		case SET_BAUD_RATE:
			printk("Dummy function to set baud rate.\n");
		break;

		case SET_STOP_BIT:
			printk("Dummy function to set stop bit.\n");
		break;

		case SET_DIRECTION:
			printk("Dummy function to set direction.\n");
		break;

		default:
			printk(KERN_ALERT "Wrong IOCTL command.\n");
			return -1;
		break;
	}
	return 0;
}
static int ioctl_init(void)
{
	int result;
	int major,minor;

	result = alloc_chrdev_region(&MyDev,0,1,"Ioctl");
	
	if(result < 0)
	{
		printk(KERN_ALERT "Device allocation is not sucessfull...!!! \n");
		return result;
	}
	
	major = MAJOR(MyDev);
	minor = MINOR(MyDev);

	printk("Device is created with major number = %d and minor number = %d \n",major,minor);

	my_cdev = cdev_alloc();
	my_cdev -> ops = &fops;

	result = cdev_add(my_cdev,MyDev,1);

	if (result < 0)
	{
		printk(KERN_ALERT "Device is not created...!!!\n");
		return result;
	}
	
	return 0;
}

static void ioctl_exit(void)
{
	printk(KERN_ALERT "Deregistering the device. Device is removed...!!!\n");
	unregister_chrdev_region(MyDev,1);
	cdev_del(my_cdev);

}

module_init(ioctl_init);
module_exit(ioctl_exit);
