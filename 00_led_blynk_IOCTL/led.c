#include <linux/module.h> /* This module defines functions such as module_init/module_exit */
#include <linux/io.h>     /* This module defines functions such as ioremap/iounmap */
#include <linux/fs.h>     /* This module defines major/minor numbers allocation functions */
#include <linux/device.h> /* This module defines functions such as class_create/device_create */
#include <linux/cdev.h>   /* This module defines functions such as cdev_init/cdev_add */
#include <linux/slab.h>   /* This module defines functions such as cdev_init/cdev_add */
#include "led.h"          /* LED modules */

#define DRIVER_AUTHOR "thonv thonv@gmail.com"
#define DRIVER_DESC "LED blinking with Ioctl()"

// a 0 a 1 is command line
#define LED_ON _IOW('a', '1', int32_t *)
#define LED_OFF _IOW('a', '0', int32_t *)

uint32_t __iomem *base_addr;

struct m_foo_dev
{
    dev_t dev_num;
    struct class *m_class;
    struct cdev m_cdev;
} mdev;

/*  Function Prototypes */
static int __init led_init(void);
static void __exit led_exit(void);
static long m_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .unlocked_ioctl = m_ioctl,
};

static long m_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
    case LED_ON:
        pr_info("LED on\n");
        *(base_addr + GPIO_SETDATAOUT_OFFSET / 4) |= LED;
        break;

    case LED_OFF:
        pr_info("LED off\n");
        *(base_addr + GPIO_CLEARDATAOUT_OFFSET / 4) |= LED;
        break;

    default:
        pr_info("Default\n");
        break;
    }

    return 0;
}

/* Constructor */
static int __init led_init(void)
{
    /* 1. Allocating device number (cat /pro/devices)*/
    if (alloc_chrdev_region(&mdev.dev_num, 0, 1, "m-cdev") < 0)
    {
        pr_err("Failed to alloc chrdev region\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d\n", MAJOR(mdev.dev_num), MINOR(mdev.dev_num));

    /* 02.1 Creating cdev structure */
    cdev_init(&mdev.m_cdev, &fops);

    /* 02.2 Adding character device to the system*/
    if ((cdev_add(&mdev.m_cdev, mdev.dev_num, 1)) < 0)
    {
        pr_err("Cannot add the device to the system\n");
        goto rm_device_numb;
    }

    /* 03. Creating struct class */
    if ((mdev.m_class = class_create(THIS_MODULE, "m_class")) == NULL)
    {
        pr_err("Cannot create the struct class for my device\n");
        goto rm_device_numb;
    }

    /* 04. Creating device*/
    if ((device_create(mdev.m_class, NULL, mdev.dev_num, NULL, "m_device")) == NULL)
    {
        pr_err("Cannot create my device\n");
        goto rm_class;
    }

    /* 05. Map GPIO-0 adress */
    base_addr = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
    if (!base_addr)
    {
        goto rm_device;
        return -ENOMEM;
    }

    /* 05.1 Set led mode as ouput then turn it on */
    *(base_addr + GPIO_OE_OFFSET / 4) &= ~LED;

    pr_info("Hello! Initizliaze successfully!\n");
    return 0;

rm_device:
    device_destroy(mdev.m_class, mdev.dev_num);
rm_class:
    class_destroy(mdev.m_class);
rm_device_numb:
    unregister_chrdev_region(mdev.dev_num, 1);
    return -1;
}

/* Destructor */
static void __exit led_exit(void)
{
    iounmap(base_addr);                         /* 05 */
    device_destroy(mdev.m_class, mdev.dev_num); /* 04 */
    class_destroy(mdev.m_class);                /* 03 */
    cdev_del(&mdev.m_cdev);                     /* 02 */
    unregister_chrdev_region(mdev.dev_num, 3);  /* 01 */

    pr_info("Good bye my fen !!!\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");