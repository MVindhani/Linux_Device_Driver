#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include"Shared_var.h"

#define NAME "Module_one"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to demostrate the functionality of Seamphores.");
MODULE_AUTHOR("Malik Vindhani");


static int module_one_init(void)
{
    int retval;
    int result;

    printk(KERN_INFO "%s is loaded..!!\n",NAME);
    
    result = get_semaphore();

    if(result == 0)
    {
        printk(KERN_INFO "%s got the semaphore..!!\n",NAME);
        retval = 0;
    }
    else
    {
        printk(KERN_INFO "%s doesn't get the semaphore..!!\n",NAME);
        retval = -EPERM;
    }

    return retval;
}

static void module_one_exit(void)
{
    printk(KERN_INFO "%s is unloaded..!!\n",NAME);
    leave_semaphore();

}

module_init(module_one_init);
module_exit(module_one_exit);