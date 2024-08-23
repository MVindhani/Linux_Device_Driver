#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

MODULE_LIECENSE("GPL");
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
 
dev_t MyTestDev;

int cal _open(struct inode *inode, struct file *filp)
{
	int minor;
	struct file_operations *cal_ptr;

	printk(KERN_INFO "Calculator driver is Open. Run appropriate app file to perform calucaltor operations\n ");
	cal_ptr = flip -> f_op;

	MyTestDev = inode -> i_rdev;
	minor = MINOR(MyTestDev);

	switch(minor)
	{
		case 0:
			cal_ptr -> read = read_add;
			cal_ptr -> write = write_add;
			printk("The File operations selected are : %p & %p\n", cal_ptr->read,cal_ptr->write);
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

}

static void calculator_exit(void)
{

}


module_init(calculator_entry);
module_exit(calculator_exit);
