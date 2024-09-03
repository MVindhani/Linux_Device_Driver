#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/fs.h>
#include<linux/uacess.h>
#include<asm/io.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to demostrate the interrupt for parallel port.");
MODULE_AUTHOR("Malik Vindhani");

#define MAJOR_NUMBER 61
#define MODULE_NAME "Parallel_port"
#define PARALLEL_DATA_PORT 0x378
#define PARALLEL_CONTROL_PORT 0x37A
#define INTERRUPT_NUMBER 7

int port;

int parallel_port_open(struct inode *inode, struct file *filp);
int parallel_port_release(struct inode *inode, struct file *filp);
ssize_t parallel_port_read(struct file *filp, char *buf,size_t count, loff_t *f_pos);
ssize_t parallel_port_write(struct file *filp, char *buf,size_t count, loff_t *f_pos);

struct file_operations parallel_port_fop = 
{
    .owner = THIS_MODULE,
    .read = parallel_port_read,
    .write = parallel_port_write,
    .open = parallel_port_open,
    .release = parallel_port_release,
};

struct tasklet_struct task;

void my_tasklet(unsigned long a)
{
    printk(KERN_INFO "This is the message from tasklet..!!!\n");
}

irqreturn_t interrupt_handler( int irq, void *id)
{
    printk(KERN_INFO "Interuupt is called..!!!\n");
    tasklet_schedule(&my_tasklet);
    printk(KERN_INFO "Now it is returned from tasklet..!! \n");
    return IRQ_HANDLED;
}

static int parallel_port_init(void)
{
    int res;
    int ret_interrupt;
    int id;
    task.func = &my_tasklet;

    printk(KERN_INFO " Entering the init module of %s\n", MODULE);

    res = register_chrdev(MAJOR_NUMBER,MODULE_NAME,&parallel_port_fop);

    if (res < 0)
    {
        printk(KERN_ALERT "Device can not be registered with Major Number %d\n", MAJOR_NUMBER);
        return res;
    }
    else
    {
        port = check_region(PARALLEL_DATA_PORT,3);   /* Check I/O port region availability.*/
        /* 
            int check_region (unsigned long start, unsigned long n);
                start :  Begin of the region.
                n     :  length of the region.
                return always 0.
        */
        if(port)
        {
            printk(KERN_ALERT "Cannot reserve the parallel port %d\n",PARALLEL_DATA_PORT);
            res = port;
        }
        else
        {
            /* Sucessfully checked the region */

            request_region(PARALLEL_DATA_PORT,3,MODULE_NAME); /* Allocate I/O port region. */
            /*
                struct resource* request_region	(unsigned long start, unsigned long	n,const char * 	name )
                    start :	begin of region
                    n 	  : length of region
                    name  :	name of requester
                    Return value is a bogus pointer. Can be ignored.
            */

            ret_interrupt = request_irq(INTERRUPT_NUMBER,interrupt_handler,IRQF_TRIGGER_RISING,"Parallel_test_device",&id);

            if (ret_interrupt)
            {
                printk(KERN_ALER " Cannot get the interrupt..!!!\n");
            }
            else
            {
                /* Interrupt is assigned sucessfully..!! */

                outb(0x10,PARALLEL_CONTROL_PORT); /* Get the control.Value written to the parallel port. This family of functions is used to do low-level port input and output. */

                return 0;
                /* 
                    void outb(unsigned char value, unsigned short port);
                */
            }
        }

        if(res != 0 )
        {
            printk(KERN_ALERT "Unloading the module as parallel port cannot be reserved..!!!\n");
            parallel_port_exit();
            return res;   
        }
    }
}

static void parallel_port_exit(void)
{
    printk(KERN_INFO " Entering the exit module of %s\n", MODULE);
    unregister_chrdev(MAJOR_NUMBER,MODULE_NAME);

    outb(0x00,PARALLEL_CONTROL_PORT); /* release the control */

    if (!port)
    {
        release_region(PARALLEL_DATA_PORT,3); /* Release I/O port region. */
    }

    free_irq(INTERRUPT_NUMBER,&id);
}

int parallel_port_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Module Opened..!!!\n");
    return 0;
}

int parallel_port_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "Module Closed..!!!\n");
    return 0;
}

ssize_t parallel_port_read(struct file *filp, char *buf,size_t count, loff_t *f_pos)
{
    char parallel_buf;

    parallel_buf = inb(PARALLEL_DATA_PORT); /* This family of functions is used to do low-level port input and output. */

    copy_to_user(buf,&parallel_buf,1);

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

ssize_t parallel_port_write(struct file *filp, char *buf,size_t count, loff_t *f_pos)
{
    char *parallel_buf;

    copy_from_user(parallel_buf,&buf,1);

    outb(parallel_buf,PARALLEL_DATA_PORT);
    return 1;

}

module_init(parallel_port_init);
module_exit(parallel_port_exit);