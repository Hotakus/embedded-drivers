//
// Created by hotakus on 9/15/23.
//

#include "common_inc.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/compiler-gcc.h>
#include <linux/device.h>
#include <asm/io.h>
#include <linux/uaccess.h>


/* functions' prototypes */
static int hello_init(void);
static void hello_exit(void);

static int hello_open(struct inode *, struct file *);
static int hello_release (struct inode *, struct file *);
static ssize_t hello_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t hello_write(struct file *, const char __user *, size_t, loff_t *);

/* module's entrance and exit */
module_init(hello_init);
module_exit(hello_exit);

/* module's information */
MODULE_AUTHOR("Hotakus <hotakus@foxmail.com>");
MODULE_DESCRIPTION("Hotakus' hello module.");
MODULE_ALIAS("hhm");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("v1.0.0");

/* variables */
static int major;                               // 主设备号
static int minor_cnt = 3;
static struct class *hello_class;               // 设备类
static struct file_operations hello_fopt = {    // 设备文件操作
    .owner = THIS_MODULE,
    .open = hello_open,
    .release = hello_release,
    .read = hello_read,
    .write = hello_write,
};

static __IO CCM_Type *reg_ccm_remap         = NULL;
static __IO GPIO_Type *reg_gpio5_remap      = NULL;
static __IO uint32_t *reg_gpio5_io3_remap   = NULL;

/* definitions */
#define DEFINE_CAT(x, y)    (x#y)
#define DRIVER_NAME         "hello_drv"
#define DRIVER_CLASS        DEFINE_CAT(DRIVER_NAME, _class)


/* functions' definitions */
int hello_init(void) {
    pr_info("Hello init by hotakus.\n");

    major = register_chrdev(0, DRIVER_NAME, &hello_fopt);

    hello_class = class_create(hello_fopt.owner, DRIVER_CLASS);
    if (IS_ERR(hello_class)) {
        pr_info( "%s line %d class create error\n", __FUNCTION__, __LINE__ );
        PTR_ERR(hello_class);
        unregister_chrdev( major, DRIVER_NAME );
        return -1;
    }

    for (int i = 0; i < minor_cnt; ++i) {
        device_create(hello_class, NULL, MKDEV(major, i), NULL, "%s_dev%d", DRIVER_NAME, i);
        pr_info("device_create (%d)\n", i);
    }

    /* ioremap */
    reg_ccm_remap = ioremap(CCM_BASE, sizeof(CCM));
    reg_gpio5_io3_remap = ioremap(IOMUXC_GET_VAL(IOMUXC_SNVS_SNVS_TAMPER3_GPIO5_IO03, muxRegister), sizeof(void*));
    reg_gpio5_remap = ioremap(GPIO5_BASE, sizeof(GPIO5));

    return 0;
}


void  hello_exit(void) {
    pr_info("Hello exit by hotakus.\n");

    iounmap(reg_gpio5_io3_remap);
    iounmap(reg_gpio5_remap);
    iounmap(reg_ccm_remap);

    for (int i = 0; i < minor_cnt; ++i) {
        device_destroy(hello_class, MKDEV(major, i));
        pr_info("device_destroy (%d)\n", i);
    }
    class_destroy(hello_class);

    unregister_chrdev(major, DRIVER_NAME);
}


int hello_open(struct inode *inode, struct file *fp) {

    /* 使能 CCM->CCGR1 的对应位 */
    /* 设置 GPIO 的功能 */
    *reg_gpio5_io3_remap &= ~(0x0f);
    *reg_gpio5_io3_remap |= 0x05;

    /* 设置 GPIO 的方向 */
    reg_gpio5_remap->GDIR |= (1<<3);   // output
    reg_gpio5_remap->DR |= (1<<3);

    return 0;
}


int hello_release (struct inode * inode, struct file * fp) {

    return 0;
}


ssize_t hello_write(struct file *fp, const char __user *buf, size_t cnt, loff_t *loff) {
    char val;
    uint32_t res = copy_from_user(&val, buf, 1);

    pr_info("copy from user: %d\n", res);

    /* 设置 GPIO 的电平高低，电平拉低点亮 */
    if (val) {
        reg_gpio5_remap->DR &= ~(1<<3);
    } else {
        reg_gpio5_remap->DR |= (1<<3);
    }

    return 0;
}


ssize_t hello_read(struct file *fp, char __user *buf, size_t cnt, loff_t *loff) {
    uint32_t res = reg_gpio5_remap->DR;
    copy_to_user(buf, &res, sizeof(res));
    return 0;
}

