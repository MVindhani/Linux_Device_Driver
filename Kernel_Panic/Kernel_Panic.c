#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A module to create kernel panic scenario");
MODULE_AUTHOR("Malik Vindhani");

int *ptr = NULL;

static int kernel_panic_init(void)
{
	printk(KERN_INFO "FIle : %s Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Module Loaded..!!");
	printk("pid = %d\t comm = %s\n",current->pid,current->comm); /* Gives current process ID & Name */
	printk("Dereferencing the pointer : %d\n",*ptr); /* Derefeerincing the NULL Pointer */
	return 0;
}

static void kernel_panic_exit(void)
{
	printk(KERN_INFO "File : %s, Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Exiting the module..!!");
}


module_init(kernel_panic_init);
module_exit(kernel_panic_exit);
