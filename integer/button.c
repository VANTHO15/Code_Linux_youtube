#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define DRIVER_AUTHOR "thonv thonv@gmail.com"
#define DRIVER_DESC "Control LED with button"

static unsigned int GPIO_BTN = 26;
static unsigned int GPIO_LED = 31;
static int irq;

static irqreturn_t btn_pushed_irq_handler(int irq, void *dev_id)
{
    int state;
    state = gpio_get_value(GPIO_LED);

    if (state == 0)
		gpio_set_value(GPIO_LED, 1);
	else
		gpio_set_value(GPIO_LED, 0);

    pr_info("BTN interrupt - LED state is: %d\n", state);
	return IRQ_HANDLED;
}

static int __init btn_init(void)
{
    int retval;

    gpio_request(GPIO_LED, "led");
    gpio_request(GPIO_BTN, "button");

    gpio_direction_input(GPIO_BTN);
    gpio_direction_output(GPIO_LED, 0);

    irq = gpio_to_irq(GPIO_BTN);
    retval = request_threaded_irq(irq, NULL,
								  btn_pushed_irq_handler,
								  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
								  "BTN-sample", NULL);

    pr_info("Hello! Initizliaze successfully!\n");
	return 0;
}


static void __exit btn_exit(void)
{
    free_irq(irq, NULL);
	gpio_free(GPIO_LED);
	gpio_free(GPIO_BTN);

    pr_info("Good bye my fen !!!\n");
}

module_init(btn_init);
module_exit(btn_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("1.0");