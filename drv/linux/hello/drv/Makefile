KVERS 			= $(shell uname -r)
LINUX_KERN_DIR 	= /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Buildroot_2020.02.x/output/build/linux-origin_master/
CUR_DIR 		= $(shell pwd)

ARCH=arm
CROSS_COMPILE	= /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-

SRCS_ALL		= $(wildcard *.c)
OBJS_ALL		= $(patsubst %.c, %.o, $(SRCS_ALL))
OBJS_SPEC		= $(filter-out %.mod.o, $(OBJS_ALL))

obj-m 				:= hello_mod_normal.o
hello_mod_normal-y 	:= hello.o hello_handle.o
ccflags-y       	:= -std=gnu99 -Wno-declaration-after-statement

build: kmod

kmod:
	@echo $(OBJS_SPEC)
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(LINUX_KERN_DIR) M=$(CUR_DIR) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(LINUX_KERN_DIR) M=$(CUR_DIR) clean
