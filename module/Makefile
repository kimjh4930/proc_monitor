KERNELDIR = /home/odroid/linux

#obj-m = getpid_4.o monitor.o cpucycle.o ipc.o
obj-m = getpid_4.o monitor_ipc.o

KDIR := /home/odroid/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
