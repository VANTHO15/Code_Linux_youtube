#include <linux/module.h>	/* This module defines functions such as module_init/module_exit */
#include <linux/io.h>		/* This module defines functions such as ioremap/iounmap */
#include "led.h"		/* LED modules */

#define DRIVER_AUTHOR "thonv tho@gmail.com"
#define DRIVER_DESC   "LED blinking"

uint32_t __iomem *base_addr;

/* Constructor */
static int __init led_init(void)
{
    base_addr = ioremap(GPIO_0_ADDR_BASE, GPIO_0_ADDR_SIZE);
    if(!base_addr)
    {
        return -ENOMEM;
    }
    *(base_addr + GPIO_OE_OFFSET/4) &=~ LED;  // mode output
    *(base_addr + GPIO_SETDATAOUT_OFFSET/4) |= LED;
    pr_info("Done !!!");
    return 0;
}

/* Destructor */
static void __exit led_exit(void)
{
    *(base_addr + GPIO_CLEARDATAOUT_OFFSET/4) |= LED;
    iounmap(base_addr);
    pr_info("Goood bye !!!");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC); 
MODULE_VERSION("1.0"); 