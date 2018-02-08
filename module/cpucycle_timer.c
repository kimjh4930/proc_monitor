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

static int keres_init(void);
static void keres_exit(void);
static void init_pmu(void);

static unsigned long read_cycles(void);

static void keres_main(unsigned long data);

unsigned long delay;

static unsigned long cycles=0;

static unsigned long long totalcycle=0;
static unsigned int precycle=0;

DEFINE_TIMER(mytimer, keres_main, 0, 0);

/* approach armv7 registers */

static void init_pmu(){

	/* Enable counter in Control Register and reset cycle count and event count */
	asm volatile("mcr   p15, 0, %0, c9, c12, 0" : : "r"(0x00000007));
	//asm volatile("mcr   p15, 0, %0, c9, c12, 0" : : "r"(0x0000000F));

        /* Event counter selection register, which counter to access */
        //asm volatile("mcr   p15, 0, %0, c9, c12, 5" : : "r"(0x0));

        /* selected event type to record, instructions executed */
        //asm volatile("mcr   p15, 0, %0, c9, c13, 1" : : "r"(0x00000008));

        /* count enable set register, bit 31 enables the cycle counter, 
           and bit 0 enables the first counter */
        asm volatile("mcr   p15, 0, %0, c9, c12, 1" : : "r"(0x8000000f));
}

static unsigned long read_cycles(){

	unsigned long cycle_count;

	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cycle_count));

        return cycle_count;

}

/* armv7 end */

static void keres_main(unsigned long data){

	//unsigned long armv7_cycle;
	//unsigned long armv7_inst;
	unsigned int temp = 0;

	cycles = read_cycles();

	//printk(KERN_INFO"cycle : %u\n", cycles);

	if(precycle > cycles){
		printk(KERN_INFO"precycle > cycles\n");
		temp = 0xFFFFFFFF - precycle;
		temp = temp + cycles;
		totalcycle = totalcycle + temp;
	}else{
		temp = cycles - precycle;
		totalcycle = totalcycle + temp;
	}

	//printk(KERN_INFO"totalcycle : %llu\n", totalcycle);

	precycle = cycles;


	/*if(cycles < 8831117){
		armv7_cycle = cycles;
		CPI = cycles * 100;
		instructions = read_instructions();
		armv7_inst = instructions;

		if(instructions != 0)
			do_div(CPI, instructions);
	}*/

	//printk("%ld\t%ld\t%lu\t%lu\n", 
	//				readcnt, writecnt, armv7_cycle, armv7_inst);
	//printk("cycle : %lu\t inst : %lu\n", armv7_cycle, armv7_inst);
	//printk("cyc : %lu,\tinst : %lu,\th_req : %lu,\t m_req : %lu\n", 
	//				cycles, instructions, temp_m_req, temp_m_req);


	//init_pmu();
	
	mod_timer(&mytimer, jiffies + delay);
}

static unsigned long get_Cycles(void){
	return cycles;
}

static int __init keres_init(void){

	init_pmu();
	printk("pmu init");

	delay = 1;

	mod_timer(&mytimer, jiffies + delay);

	return 0;
}

static void __exit keres_exit(void){

	del_timer(&mytimer);

	printk("keres exit\n");

}

EXPORT_SYMBOL( get_Cycles );

module_init(keres_init);
module_exit(keres_exit);

MODULE_LICENSE("Dual BSD/GPL");
