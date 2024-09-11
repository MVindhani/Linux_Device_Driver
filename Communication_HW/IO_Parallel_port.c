#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/uaccess.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/ioport.h>
#include<asm/io.h>

#define MAJOR_NUMBER 60
#define MODULE_NAME "Parallel_port_IO"
#define PARALLEL_DATA_PORT 0x378
#define PARALLEL_CONTROL_PORT 0x37A 

struct file_operations parallel_fops = 
{
    .owner = THIS_MODULE,
    .read = parallel_io_read,
    .write = parallel_io_write,
    .open = parallel_io_open,
    .release = parallel_io_release,
};

int parallel_io_open(struct inode *inode, struct file *filp);
int parallel_io_release(struct inode *inode, struct file *filp);
ssize_t parallel_io_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t parallel_io_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);

int port;

int parallel_io_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Module is open..!!!\n");
    return 0;
}

int parallel_io_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Module is closed...!!!\n");
    return 0;
}

static int parallel_port_io_init(void)
{
    int result;

    result = register_chrdev(MAJOR_NUMBER,MODULE_NAME,&parallel_fops);
    if(register_chrdev < 0)
    {
        printk(KERN_ALERT "Cannot obtain the major number..!!!\n");
        return result;
    }
    else
    {
        port = check_region(PARALLEL_DATA_PORT,3);    /*  This function allows your driver to check to see whether a given set of I/O ports is available*/

        if(port)
        {
            printk(KERN_ALERT "Cannot reserve the port...!!!\n");
            parallel_port_io_exit();
            return -1;
        }
        else
        {
            request_region(PARALLEL_DATA_PORT,3,MODULE_NAME);
            printk(KERN_INFO "Parallel port is assigned..!!\n");
            return 0;
        }
    }
}

ssize_t parallel_io_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    char parallel_port_buf;

    parallel_port_buf = inb(PARALLEL_DATA_PORT);

    copy_to_user(buf,&parallel_port_buf,1);

    printk(KERN_INFO "Data is read..!!!\n");

    if(*f_pos == 0)
    {
        *f_pos += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

ssize_t parallel_io_write(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    char *parallel_port_buf;

    copy_from_user(parallel_port_buf,&buf,1);

    outb(parallel_port_buf,PARALLEL_DATA_PORT);

    printk(KERN_INFO "Data is written..!!!\n");

    return 1;
}

static void parallel_port_io_exit(void)
{
    unregister_chrdev(MAJOR_NUMBER,MODULE_NAME);

    if(!port)
    {
        release_region(PARALLEL_DATA_PORT,3);
    }
    printk(KERN_INFO "Parallel port is removed..!!!\n");
}

module_init(parallel_port_io_init);
module_exit(parallel_port_io_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to demostrate communicating with parallel IO port");
MODULE_AUTHOR("Malik Vindhani");