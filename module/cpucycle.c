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

static int  pmucycle_init (void);
static void pmucycle_exit (void);
static void enable_cycle  (void);

/* approach armv7 registers */
static void enable_cycle(){

        /* Enable counter in Control Register and reset cycle count and event count */
        asm volatile("mcr   p15, 0, %0, c9, c12, 0" : : "r"(0x00000007));
        
	/* count enable set register, bit 31 enables the cycle counter, 
           and bit 0 enables the first counter */
        asm volatile("mcr   p15, 0, %0, c9, c12, 1" : : "r"(0x8000000f));
}

static int __init pmucycle_init(void){

        enable_cycle();

        printk("pmucycle_init\n");

        return 0;
}

static void __exit pmucycle_exit(void){

        printk("pmucycle exit\n");

}

module_init(pmucycle_init);
module_exit(pmucycle_exit);

MODULE_LICENSE("Dual BSD/GPL");
