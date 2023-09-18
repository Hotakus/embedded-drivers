KVERS 			= $(shell uname -r)
LINUX_KERN_DIR 	= /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/Buildroot_2020.02.x/output/build/linux-origin_master/
# ~/workspace/drivers/100ask_imx6ull_mini-sdk/Linux-4.9.88/ # /lib/modules/$(KVERS)/build/
CUR_DIR 		= $(shell pwd)

ARCH=arm
CROSS_COMPILE	= /home/hotakus/workspace/drivers/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-
#~/dl/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-

SRCS_ALL		= $(wildcard *.c)
OBJS_ALL		= $(patsubst %.c, %.o, $(SRCS_ALL))
OBJS_SPEC		= $(filter-out %.mod.o, $(OBJS_ALL))

obj-m 				:= hello_mod_normal.o
hello_mod_normal-y 	:= hello.o
ccflags-y       	:= -std=gnu99 -Wno-declaration-after-statement

build: kernel_modules

kernel_modules:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(LINUX_KERN_DIR) M=$(CUR_DIR) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(LINUX_KERN_DIR) M=$(CUR_DIR) clean
