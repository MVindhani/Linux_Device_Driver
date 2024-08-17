#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include "add.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is moudle to calculate avergae");
MODULE_AUTHOR("Malik Vindhani");

static int avg_init(void)
{
	printk("File : %s Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Average fun : Init \n");
	printk("Averge is %d\n",add(10,20)/2); /* add() function is defined in add.c file */
	return 0;
}

static void avg_exit(void)
{
	printk("File : %s Function : %s Line : %d\n",__FILE__,__func__,__LINE__);
	printk("Average fun : Exit \n");
}


module_init(avg_init);
module_exit(avg_exit);
