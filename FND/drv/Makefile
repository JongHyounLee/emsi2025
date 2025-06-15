obj-m := fnddrv.o
 KDIR := /home/ausu/develop/linux_kernel/   
PWD := $(shell pwd) 
export ARCH=arm
export CROSS_COMPILE=/home/ausu/develop/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	-rm*.o  *.mod.c.*.cmdmodules.order Module.symvers
