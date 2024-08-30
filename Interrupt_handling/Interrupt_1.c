#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/io.h>

#define NUMBER_OF_INTERRUPT 1

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to describe the demostration of interrupt handling in linux");
MODULE_AUTHOR("Malik Vindhani");

int id;
int count = 0;

irqreturn_t  interrupt_handler(int irq, void *id)
{
    printk(KERN_INFO "Inside interrupt handler..!!!\n");
    count++;
    printk("count value is %d\n",count);
    return IRQ_HANDLED;
}

static int interrupt_one_init(void)
{
    int res;

    res = request_irq(NUMBER_OF_INTERRUPT,interrupt_handler,IRQF_SHARED,"interrupt_device",&id);
    /*
    int request_irq(unsigned int irq, void (*handler)(int, void *, struct pt_regs *), unsigned long irqflags, const char *devname, void *dev_id) 
            irq = Interrupt Number,
            void handler(int, void*) = It is pointer which will point to the function which will handle the interrupt.
            irqflags = A flags for interrupt handler.  IRQF_SHARED --> It means that the interrupt can be shared with other devices.
            *devname = Name of the device for which interrupt is assigned.
            dev_id = device ID. It can be NULL, but if we are using IRQ_SHARED then it cannot be NULL.
    */
    printk("Return value of request interrupt is :%d\n",res);

    if(res < 0)
    {
        printk(KERN_ALERT "Interrupt cannot be created...!!!\n");
        return -1;
    }
    else
    {
        printk(KERN_INFO " Interrupt created..!!!\n");
        return 0;
    }

}

static void interrupt_one_exit(void)
{
    printk("Device is unloaded..!!!\n");
    free_irq(NUMBER_OF_INTERRUPT,&id);

    /*
    void free_irq(unsigned int irq, void * dev_id);
        irq = Interrupt Number,
        dev_id = device ID. 
    */

}

module_init(interrupt_one_init);
module_exit(interrupt_one_exit);