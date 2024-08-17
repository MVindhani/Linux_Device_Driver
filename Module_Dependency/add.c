#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include "add.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to add 2 numbers");
MODULE_AUTHOR("Malik Vindhani");

int add (int x, int y)
{
	printk("This is add function..!! \n");
	return x + y;
}

/* This macro is used to add the dependency variable/parameter while compilation.*/

EXPORT_SYMBOL(add);

/* It can be seen in Modules.sysver intermediate file generated while compilation */

static int add_init(void)
{
	/* This function shall be used in another file */

	printk("File : %s Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Add function :Init\n");
	
	return 0;
}

static void add_exit(void)
{
	printk("File : %s Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Add function :Exit \n");
}


module_init(add_init);
module_exit(add_exit);
