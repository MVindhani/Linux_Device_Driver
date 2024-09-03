#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/interrupt.h>
#define NUMBER_OF_INTERRUPT 1

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to demostrate the functionality of tasklet");
MODULE_AUTHOR("Malik Vindhani");

/* The tasklet_struct structure (see Figure 2), which includes the necessary data to manage and 
   maintain the tasklet (state, enable/disable via an atomic_t, function pointer, data, and linked-list reference).
*/

struct tasklet_struct task;
int count = 0,id;

/* Tasklets are a deferral scheme that you can schedule for a registered function to run later. 
   The top half (the interrupt handler) performs a small amount of work, and then schedules the
   tasklet to execute later at the bottom half. */
void my_tasklet(unsigned long)
{
    printk(KERN_INFO "Inside tasklet...Tasklet is called..!!\n");
}

irqreturn_t  interrupt_handler(int irq, void *id)
{
    printk(KERN_INFO "Interrupt handler is called..!!\n");
    printk("value of count is %d\n",count);
    tasklet_schedule(&task); /* Scheduling the tasklet. */
    count++;
    printk(KERN_INFO "Tasklet is calling..!!\n");
    printk("value of count is %d\n",count);
    return IRQ_HANDLED;
}

static int interrupt_tasklet_init(void)
{
    int res;
    task.func = &my_tasklet; /* Assigning the tasklet to the function pointer in the tasklet structure.*/
    printk(KERN_INFO "Module is loaded...!!!\n");
    res = request_irq(NUMBER_OF_INTERRUPT,interrupt_handler,IRQF_SHARED,"interrupt_device_tasklet",&id);
    /*
    int request_irq(unsigned int irq, void (*handler)(int, void *, struct pt_regs *), unsigned long irqflags, const char *devname, void *dev_id) 
            irq = Interrupt Number,
            void handler(int, void*) = It is pointer which will point to the function which will handle the interrupt.
            irqflags = A flags for interrupt handler.  IRQF_SHARED --> It means that the interrupt can be shared with other devices.
            *devname = Name of the device for which interrupt is assigned.
            dev_id = device ID. It can be NULL, but if we are using IRQ_SHARED then it cannot be NULL.
    */
    
    if(res < 0)
    {
        printk(KERN_ALERT "Interrupt cannot be created...!!!\n");
        return res;
    }
    else
    {
        return 0;
    }
}

static void interrupt_tasklet_exit(void)
{
    printk(KERN_INFO "Module is unloaded...!!!\n");
    free_irq(NUMBER_OF_INTERRUPT,&id);
    /*
    void free_irq(unsigned int irq, void * dev_id);
        irq = Interrupt Number,
        dev_id = device ID. 
    */
}

module_init(interrupt_tasklet_init);
module_exit(interrupt_tasklet_exit);