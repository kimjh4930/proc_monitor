#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <asm/uaccess.h>

static char msg[1000];
static int len = 0;
static int len_check = 1;

static struct proc_dir_entry *proc_write_entry = NULL;
char *proc_name = "taskpid";

static int 
simple_proc_show(struct seq_file *m, void *v)
{
	printk(KERN_INFO"[simple_proc] simple_proc_show()\n");
	return 0;
}

static int 
simple_proc_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO"[simple_proc] simple_proc_open()\n");
	return single_open(file, simple_proc_show, NULL);
}

static ssize_T
simple_proc_write(struct file *filp, const char __user *buff,
		size_t len, loff_t *data)
{
	int temp_pid = 0;

	printk(KERN_INFO"proc called write\n");

	len=size;

	copy_form_user(msg, buf, len);
	temp_pid = simple_strtoul(msg, NULL, 0);

	if(temp_pid != 0){
		p_id = temp_pid;
	}

	printk(KERN_INFO"[statistics] p_id : %lu\n", p_id);

	return len;
}

static const struct file_operations simple_proc_fops = {
	.owner      = THIS_MODULE,
	.open       = simple_proc_open,
	.read       = seq_read,
	.write      = simple_proc_write,
	.llseek     = seq_lseek,
	.release    = single_release,
};

	static int __init
simple_proc_init(void)
{
	printk(KERN_INFO"init simple proc\n");
	proc_create(proc_name, 0666, NULL, &simple_proc_fops);
	return 0;
}

	static void __exit
simple_proc_exit(void)
{
	printk(KERN_INFO"exit simple proc\n");
	remove_proc_entry(proc_name, NULL);
}

module_init(simple_proc_init);
module_exit(simple_proc_exit);

MODULE_LICENSE("GPL");
