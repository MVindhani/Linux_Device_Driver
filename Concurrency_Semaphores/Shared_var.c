#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/semaphores.h>
#include"Shared_var.h"

#define NAME "Shared_Var"

struct semaphore new_semaphore;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to export shared variables used to demostrate the functionality of Seamphores.");
MODULE_AUTHOR("Malik Vindhani");

static int get_semaphore(void)
{
    down(&new_semaphore); /* Decreament the semaphore count value and lock it.*/
    printk(KERN_INFO "Semaphore is locked...!!\n");
    return 0;
}

static void leave_semaphore(void)
{
    up(&new_semaphore); /* Increment the semaphore count value and unlock it.*/
    printk(KERN_INFO "Semaphore is released and count is %d\n",new_semaphore.count);
}

EXPORT_SYMBOL_GPL(get_semaphore); /* EXPORT_SYMBOL_GPL() will export symbol such that it can be used by all the modules under GPL license. Others cannot use it.*/
EXPORT_SYMBOL_GPL(leave_semaphore);


static int shared_var_init(void)
{
    printk(KERN_INFO "Module %s is loaded....!!\n",NAME);
    sema_init(&new_semaphore,1);
    return 0;
}

static void shared_var_exit(void)
{
    printk(KERN_INFO "Module %s is unloaded....!!\n",NAME);
}

module_init(shared_var_init);
module_exit(shared_var_exit);