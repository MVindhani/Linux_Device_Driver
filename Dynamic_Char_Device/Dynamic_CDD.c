#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to create device with dynamic major number");
MODULE_AUTHOR("Malik Vindhani");

ssize_t dynamic_read (struct file *, char __user *, size_t, loff_t *);
ssize_t dynamic_write (struct file *, const char __user *, size_t, loff_t *);
int dynamic_open (struct inode *, struct file *);
int dynamic_release (struct inode *, struct file *);

struct file_opertaions f_ops = 
{
    .owner = THIS_MODULE,
    .read = dynamic_read,
    .write = dynamic_write,
    .open = dynamic_open,
    .release = dynamic_release,
};

struct cdev *my_cdev; /* The struct cdev is the kernel’s internal structure that represents char devices. */

dev_t Mydev; /* Used for device IDs.  It is an integer type. A device ID consists of two parts: Major ID & Minor ID*/

int dynamic_open (struct inode *inode, struct file *flip)
{
    printk(KERN_INFO "File : %s, Function : %s, Line = %d\n",__FILE__,__func__,__LINE__);
    printk("Driver is open...!!\n");
    return 0;
}

int dynamic_release (struct inode *inode, struct file *flip)
{
    printk(KERN_INFO "File : %s, Function : %s, Line = %d\n",__FILE__,__func__,__LINE__);
    printk("Driver is closed...!!\n");
    return 0;
}

ssize_t dynamic_read (struct file *flip, char __user *buf, size_t count, loff_t *f_pos)
{
    int result,retval;;
    char Kbuff[] = "This is from Kernel Buffer";
    printk(KERN_INFO "File : %s, Function : %s, Line = %d\n",__FILE__,__func__,__LINE__);
    printk("Driver is in read mode...!!\n");

    result = copy_to_user(buf,Kbuff,sizeof(Kbuff)); /* Destination, source, size */
    if(result == 0)
    {
        printk(KERN_INFO "Copy data to User Space from Kernel Space\n");
        printk(KERN_INFO "The written data is of %d size \n", sizeof(Kbuff));
        
        if(*f_pos == 0)
        {
            retval = sizeof(Kbuff);
            *f_pos = retval;
        }
        else
        {
            retval = 0;
        }
    }
    else
    {
        printk(KERN_ALERT "Error in writing the data to user\n");
        retval = -EFAULT; 
    }

    return retval;

}

ssize_t dynamic_write (struct file *flip, const char __user *buf, size_t count, loff_t *f_pos)
{
    int result, retval;
    char Kbuff[120];
    printk(KERN_INFO "File : %s, Function : %s, Line = %d\n",__FILE__,__func__,__LINE__);
    printk("Driver is in write mode...!!\n");

    result = copy_from_user(Kbuff,buf,count); /* Destination, source, size*/

    if (result == 0)
    {
        printk(KERN_INFO "Copy data to Kernel Space to User Space\n");
        printk(KERN_INFO "The written data is of %d size \n", count);
        retval = count;    
    }
    else
    {
        printk(KERN_ALERT "Error in writing the data to Kernel\n");
        retval = -EFAULT;       
    }

    return retval;
}

static int dynamic_module_init(void)
{
    int result;
    int Major, Minor;
    
    /* Allocates a range of char device numbers. The major number will be chosen dynamically, and returned (along with the first minor number) in dev. Returns zero or a negative error code.*/
    result = alloc_chrdrv_region(&Mydev,0,4,"DynamicCharDriver");

    if (result < 0)
    {
        printk(KERN_ALERT "The region requested cannot be allocated\n");
        return result;
    }

    Major = MAJOR(Mydev); /*MAJOR is a macro which will extract the major number from the Mydev */
    Minor = MINOR(Mydev); /*MINOR is a macro which will extract the minor number from the Mydev */

    printk(KERN_INFO "Device is registered with Major number %d and Minor number %d\n",Major,Minor);
    
    my_cdev = cdev_alloc(); /* Allocates memory to Char device structure and returns a cdev structure, or NULL on failure. */
    my_cdev->ops = &f_ops; /* Link file operation with the file operation of Char device */

    result = cdev_add(my_cdev,Mydev,4); /* Notify the kernel abt the new device. cdev_add() adds the device represented by p to the system, making it live immediately. A negative error code is returned on failure.*/

    if (result < 0)
    {
        printk(KERN_ALERT "The Char device is not created\n");
        return result;       
    }

    return 0;
}

static void dynamic_module_exit(void)
{
    unregister_chrdrv_region(Mydev,4); /* Unregister the device numbers and the device created */
    cdev_del(my_cdev); /* cdev_del() removes p from the system, possibly freeing the structure itself. */

    /*This guarantees that cdev device will no longer be able to be opened, however any cdevs already open will remain and their fops will still be callable even after cdev_del returns*/

    printk(KERN_INFO "Char driver is removed\n");
}


module_init(dynamic_module_init);
module_exit(dynamic_module_exit);