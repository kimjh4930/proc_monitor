KERNELDIR = /home/odroid/linux

obj-m = cpucycle.o ipc.o

KDIR := /home/odroid/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
