#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h> /* printk() */
#include<linux/slab.h> /* kmalloc() */ 
#include<linux/fs.h> /* file system */
#include<linux/errno.h> /* error codes */
#include<linux/uaccess.h> /* copy_from / copy_to */

MODULE_LICENSE("GPL");

int memory_major = 61; /* Major Number */
char *memory_buffer;

ssize_t memory_read (struct file *, char __user *, size_t, loff_t *);
ssize_t memory_write (struct file *, const char __user *, size_t, loff_t *);
int memory_open (struct inode *, struct file *);
int memory_release (struct inode *, struct file *);


struct file_operations memory_fops =
{
	.read = memory_read,
	.write = memory_write,
	.open = memory_open,
	.release = memory_release,
};

int memory_open (struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG "%s : %s : %d\n",__FILE__,__func__,__LINE__);
	return 0;
}

int memory_release (struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG "%s : %s : %d\n",__FILE__,__func__,__LINE__);
	return 0;
}

ssize_t memory_read (struct file *flip, char __user *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "%s : %s : %d, count : %d, *f_pos : %d\n",__FILE__,__func__,__LINE__, count, *f_pos);

	copy_to_user(buf,memory_buffer,6); /* copy_to_user(destination_user,source_kernel,length) */

	if(*f_pos == 0)
	{
		*f_pos += 1;
		return 1;
	}
	else
	{
		return 0; // EOF;
	}
}

ssize_t memory_write (struct file *flip, const char __user *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "%s : %s : %d, count : %d, *f_pos : %d\n",__FILE__,__func__,__LINE__, count, *f_pos);
	
	copy_from_user(memory_buffer,buf,6); /* copy_from_user(destination_kernel,source_user,length) */

	return 1;
}

/* Memory Exit */
static void  memory_exit(void)
{
	unregister_chrdev(memory_major,"MyMemory");
	
	if(memory_buffer)
	{
		kfree(memory_buffer);
	}
	
	printk("Removing Memory Module\n");
}

/* Memory init */
static int memory_init(void)
{
	int result;

	result = register_chrdev(memory_major,"MyMemory",&memory_fops);
	
	if ( result < 0 )
	{
		printk("Memory : Cannot obtain Major Number %d\n", memory_major);
		return result;
	}

	memory_buffer = kmalloc(1,GFP_KERNEL); /* Refer slab.h header fiel for its definition and macor meanings */
	if(!memory_buffer)
	{
		result = -ENOMEM;
		goto fail;
	}
	
	memset(memory_buffer,0,1);

	printk("Inserting Memory Module \n");

	return 0;
	
	fail:
		memory_exit();
		return result;
}


module_init(memory_init);
module_exit(memory_exit);
