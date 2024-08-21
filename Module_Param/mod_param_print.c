#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This module prints the value and number of iterations as per input value");
MODULE_AUTHOR("Malik Vindhani");

static char *what = "World";
module_param(what,charp,0644);
static int repeat = 1;
module_param(repeat,int,0644);

static int module_param_init(void)
{
	int i = 0;

	for(i = 0; i < repeat; i++)
	{
		printk("Hello %s\n",what);
	}

	return 0;

}

static void module_param_exit(void)
{
	printk("Module param exit function\n");

}


module_init(module_param_init);
module_exit(module_param_exit);
