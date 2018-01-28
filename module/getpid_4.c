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

int p_id;

char *proc_name = "taskpid";

static int 
taskpid_proc_show(struct seq_file *m, void *v)
{
	printk(KERN_ALERT"[taskpid] task_proc_show()\n");
	return 0;
}

static int 
taskpid_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, taskpid_proc_show, NULL);
}

static ssize_t
taskpid_proc_write(struct file *filp, const char __user *buf,
		size_t size, loff_t *offset)
{
	int temp_pid;

	printk(KERN_ALERT"[taskpid] taskpid_proc_write()\n");

	len = size;
	copy_from_user(msg, buf, len);
	temp_pid = simple_strtoul(msg, NULL, 0);

	if(temp_pid != 0){
		p_id = temp_pid;
	}

	return len;
}

static int get_PID(void){
	return p_id;
}

static void set_PID(int value){
	p_id = value;
}

static const struct file_operations taskpid_proc_fops = {
	.owner      = THIS_MODULE,
	.open       = taskpid_proc_open,
	.read       = seq_read,
	.write      = taskpid_proc_write,
	.llseek     = seq_lseek,
	.release    = single_release,
};

static int __init
taskpid_proc_init(void)
{
	proc_create(proc_name, 0666, NULL, &taskpid_proc_fops);
	return 0;
}

static void __exit
taskpid_proc_exit(void)
{
	remove_proc_entry(proc_name, NULL);
}

EXPORT_SYMBOL(get_PID);
EXPORT_SYMBOL(set_PID);

module_init(taskpid_proc_init);
module_exit(taskpid_proc_exit);

MODULE_LICENSE("GPL");
