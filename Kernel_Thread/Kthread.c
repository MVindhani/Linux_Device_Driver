#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kthread.h>
#include<linux/jiffies.h>
#include<linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to describe the working of kernel threads.");
MODULE_AUTHOR("Malik Vindhani");

static struct task_struct *my_thread = NULL; /*It is a kernel structure to represent a process adn its threads in linux kernel*/

static int my_thread_func(void *data)
{

    printk(KERN_INFO "Thread is started and below are its details : \n");
    printk("Name : %s, PID : %d, TID : %d\n", current->comm,current->pid,current->tgid); 

    while(1)
    {
        printk("This is kernel thread...!!!\n");
        set_current_state(TASK_INTERRUPTIBLE); /*It changes the state of the task from TASK_RUNNING to TASK_INTTERUPTIBLE*/
        schedule_timeout(msecs_to_jiffies(3000)); /*After task state set, this function causes the sleep untill the given time is passed. Internally kernel uses jiffies to calculate the time.*/
        schedule(); /* Thsi function is used to schedule the best runnable task. Invoking the scheduler manually.*/

        if(kthread_should_stop()) /* This function will wait till kthread_stop() is called. Hence, infinite loop here.*/
            break;

    }
    return 0;
}

static int my_kthread_init(void)
{
    /* 
    kthread_run() -->> This function will internall call kthread_create(). Refer to linux/kthread.h file for more info .
    kthread_run(threadfunc,data,namefmt)
                threadfunc -- thread function to run until signal is pending.
                data       -- data pointer for @threadfuc.
                namefmt    -- printf-style name for the thread.
    */

    my_thread = kthread_run(my_thread_func,NULL,"my_thread"); 
    
    /* IS_ERR : It is macro which will check if the given pointer is sucessfully created. Refer err.h file. */
    /* PTR_ERR : It is macro which will extract the error from the pointer. Refer err.h file. */
    
    if(IS_ERR(my_thread))
    {
        printk(KERN_ALERT "Error %ld in creating the kernel thread.\n",PTR_ERR(my_thread));
        return -1;
    }

    printk(KERN_INFO " STarting the kernel thread.\n");
    return 0;
}

static void my_kthread_exit(void)
{
    printk("Kernel thread is exiting.\n");
    kthread_stop(my_thread); /* It will stop the thread created by kthread_create().*/
}


module_init(my_kthread_init);
module_exit(my_kthread_exit);