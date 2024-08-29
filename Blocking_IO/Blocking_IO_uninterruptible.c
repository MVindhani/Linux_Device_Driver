#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/wait.h>

#define MAJOR_NUMBER 60
#define NAME "Sleepy_Device"
#define DATA_NOT_PRESENT 0
#define DATA_AVAILABLE 1

int data_present = DATA_NOT_PRESENT;
wait_queue_head my_queue; /* It is wait queue structure */
DECLARE_WAIT_QUEUE_HEAD(my_queue) /* It is used to initialize the wait queue at compile time*/

struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .read = sleep_read,
    .write = sleep_write,
    .open = sleep_open,
    .release = sleep_release,
};

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to describe the uninterruptable sleep");
MODULE_AUTHOR("Malik Vindhani");

ssize_t sleep_read(struct file *, char __user *, size_t, loff_t *);
ssize_t sleep_write(struct file *, const char __user *, size_t, loff_t *);
int sleep_open(struct inode *, struct file *);
int sleep_release(struct inode *, struct file *);

ssize_t sleep_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *f_offseet)
{
    if(data_present == DATA_NOT_PRESENT)
    {
        printk(KERN_ALERT "Data is not available. Process %s is going to sleep.\n",current->comm);
        wait_event(my_queue,(data_present==DATA_AVAILABLE)); /* This is a uniterruptible sleep */
    }
    else
    {
        printk("Data is avaialble in the buffer...!!!\n");
    }
    return count;
}

ssize_t sleep_write(struct file *flip, const char __user *Ubuff, size_t len, loff_t *f_offset)
{
    printk("Trying to write the data.\n");
    data_present = DATA_AVAILABLE;
    wake_up(&my_queue);
    return len;
}

int sleep_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Device is open\n");
    return 0;
}

int sleep_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Device is close\n");
    return 0;
}

static int blocking_io_init(void)
{
    int result;
    int retval;

    result = register_chrdev(MAJOR_NUMBER,NAME,&fops);

    if(result < 0)
    {
        printk(KERN_ALERT "Device is not registered..!!!\n");
        retval = result;
    }
    else
    {
        printk(KERN_INFO "Device is registered with Major Numebr %d\n",MAJOR_NUMBER);
        retval = 0;
    }
    return retval;
}

static void blocking_io_exit(void)
{
    printk(KERN_INFO "Device is unregistered now..!!!\n");
    unregister_chrdev(MAJOR_NUMBER,NAME);
}

module_init(blocking_io_init);
module_exit(blocking_io_exit);