#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/spinlock.h>

//timer
#include <linux/timer.h>
#include <linux/jiffies.h>

static int  pmucycle_init (void);
static void pmucycle_exit (void);
static void enable_cycle  (void);
static void measure_main(unsigned long data);
static unsigned long read_cycle(void);
static unsigned long read_instruction(void);

unsigned long delay;

DEFINE_TIMER(mytimer, measure_main, 0, 0);

/* approach armv7 registers */
static void enable_cycle(){

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

static void measure_main(unsigned long data){

	unsigned long cpu_cycle = read_cycle();
	unsigned long cpu_inst = read_instruction();

	printk("cycle : %lu\t inst : %lu\n", cpu_cycle, cpu_inst);

	mod_timer(&mytimer, jiffies + delay);
}

static int __init pmucycle_init(void){

        enable_cycle();

        printk("pmucycle_init\n");

	delay = 10;
	mod_timer(&mytimer, jiffies + delay);

        return 0;
}

static void __exit pmucycle_exit(void){

        printk("pmucycle exit\n");

}

EXPORT_SYMBOL( read_cycle );
EXPORT_SYMBOL( read_instruction );

module_init(pmucycle_init);
module_exit(pmucycle_exit);

MODULE_LICENSE("Dual BSD/GPL");
