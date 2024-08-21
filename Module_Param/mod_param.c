#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module with input parameters");
MODULE_AUTHOR("Malik Vindhani");



int temp = 10;
module_param(temp,int,0644);
static int module_param_init(void)
{
	printk("This is module param init function. The value of temp is %d\n",temp);
	return 0;
}

static void module_param_exit(void)
{
	printk("This is module param exit function\n");
}



module_init(module_param_init);
module_exit(module_param_exit);
