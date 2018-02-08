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

static int pmycycle_init(void);
static int pmucycle_exit(void);
static void enable_pmu(void);

static unsigned long read_cycle(void);
static unsigned long read_instruction(void);

u64 total_cycle, total_inst;

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

/* approach armv7 registers */
static void enable_pmu(){

        /* Enable counter in Control Register and reset cycle count and event count */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" : : "r"(0x00000007));

	asm volatile("mcr p15, 0, %0, c9, c12, 5" : : "r"(0x0));

	asm volatile("mcr p15, 0, %0, c9, c13, 1" : : "r"(0x00000008));
        
	/* count enable set register, bit 31 enables the cycle counter, 
           and bit 0 enables the first counter */
        asm volatile("mcr   p15, 0, %0, c9, c12, 1" : : "r"(0x8000000f));

}

static unsigned long read_cycle(){

	unsigned long cycle_count;

	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cycle_count));

	return cycle_count;
}

static unsigned long read_instruction(){
	unsigned long instr_count;

	asm volatile("mrc p15, 0, %0, c9, c12, 5" : : "r"(0x0));
	asm volatile("mrc p15, 0, %0, c9, c13, 2" : "=r"(instr_count));

	return instr_count;
}

static void pid_monitor(unsigned long data){

	u32 cur_cycle=0, cur_inst=0;
	
	pid = get_PID();

	pid_struct = find_get_pid(pid);
	task = pid_task(pid_struct, PIDTYPE_PID);

	if(task != NULL){
		isRunning = 1;
		se = task->se;
		statistics = se.statistics;

		total_cycle += read_cycle();
		total_inst += read_instruction();

	}else{
		isRunning = 0;
	}

	if(!isRunning){

		if(pid != 0){
			printk(KERN_INFO"[monitor] pid : %d\n", pid);

			printk("total_cycle : %llu\ttotal_inst : %llu\n", total_cycle, total_inst);
			
			//in cputime
/*			printk(KERN_INFO"[monitor] exec : %lld.%06ld\n", SPLIT_NS((long long)se.sum_exec_runtime));
			printk(KERN_INFO"[monitor] sleep : %lld.%06ld\n", SPLIT_NS((long long)statistics.sum_sleep_runtime));
			printk(KERN_INFO"[monitor] block : %lld.%06ld\n", SPLIT_NS((long long)statistics.block_max));

			printk(KERN_INFO"[monitor] execl : %llu\n", se.sum_exec_cycle);
			printk(KERN_INFO"[monitor] slpcl : %llu\n", statistics.sleep_sum_cycle);
			printk(KERN_INFO"[monitor] blkcl : %llu\n", statistics.block_sum_cycle);

			printk(KERN_INFO"[monitor] waitcnt : %llu\n", statistics.wait_count);
			printk(KERN_INFO"[monitor] blkcnt : %llu\n", statistics.iowait_count);*/
			set_PID(0);
		}
	}

	enable_pmu();

	mod_timer(&mytimer, jiffies + delay);

}

static int __init pid_monitor_init(void){

	printk(KERN_INFO"[monitor] init\n");

	enable_pmu();

	total_cycle = 0;
	total_inst = 0;

	delay = 1;
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
