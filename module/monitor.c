#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

//timer
#include <linux/timer.h>
#include <linux/jiffies.h>

//task
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/sched.h>

int delay;
int pid = 0;
int isRunning = 0;

struct pid *pid_struct;
struct task_struct *task;

struct sched_entity se;
struct sched_statistics statistics;

struct task_cputime cputime;

int get_PID(void);
void set_PID(int);

static void pid_monitor(unsigned long);


DEFINE_TIMER(mytimer, pid_monitor, 0, 0);

static long long nsec_high(unsigned long long nsec){
	if((long long)nsec < 0){
		nsec = -nsec;
		do_div(nsec, 1000000);
		return -nsec;
	}
	do_div(nsec, 1000000);

	return nsec;
}

static unsigned long nsec_low(unsigned long long nsec){
	if((long long)nsec < 0)
		nsec = -nsec;
	
	return do_div(nsec, 1000000);
}

#define SPLIT_NS(x) nsec_high(x), nsec_low(x)

static void pid_monitor(unsigned long data){
	
	pid = get_PID();

	pid_struct = find_get_pid(pid);
	task = pid_task(pid_struct, PIDTYPE_PID);

	if(task != NULL){
		isRunning = 1;
		se = task->se;
		statistics = se.statistics;

		printk(KERN_INFO"[monitor] execl : %llu\n", se.sum_exec_cycle);
                printk(KERN_INFO"[monitor] slpcl : %llu\n", statistics.sleep_sum_cycle);
                printk(KERN_INFO"[monitor] blkcl : %llu\n", statistics.block_sum_cycle);

		//cputime = task->cputime_expires;

		//printk(KERN_INFO"[monitor]")
		//printk(KERN_INFO"[monitor] exec : %lld.%06ld\n", SPLIT_NS((long long)se.sum_exec_runtime));

	}else{
		isRunning = 0;
	}

	if(!isRunning){

		if(pid != 0){
			printk(KERN_INFO"[monitor] pid : %d\n", pid);
			
			//in cputime
			printk(KERN_INFO"[monitor] exec : %lld.%06ld\n", SPLIT_NS((long long)se.sum_exec_runtime));
			printk(KERN_INFO"[monitor] sleep : %lld.%06ld\n", SPLIT_NS((long long)statistics.sum_sleep_runtime));
			printk(KERN_INFO"[monitor] block : %lld.%06ld\n", SPLIT_NS((long long)statistics.block_max));

			printk(KERN_INFO"[monitor] execl : %llu\n", se.sum_exec_cycle);
			printk(KERN_INFO"[monitor] slpcl : %llu\n", statistics.sleep_sum_cycle);
			printk(KERN_INFO"[monitor] blkcl : %llu\n", statistics.block_sum_cycle);
			set_PID(0);
		}
	}

	mod_timer(&mytimer, jiffies + delay);

}

static int __init pid_monitor_init(void){

	printk(KERN_INFO"[monitor] init\n");

	delay = 10;
	mod_timer(&mytimer, jiffies + delay);

	return 0;
}

static void __exit pid_monitor_exit(void){
	printk(KERN_INFO"[monitor] exit\n");
	del_timer(&mytimer);
}

module_init(pid_monitor_init);
module_exit(pid_monitor_exit);
MODULE_LICENSE("GPL");
