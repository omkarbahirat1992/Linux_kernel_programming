#include <linux/kernel.h>
#include <linux/module.h>

void only_exit_module(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
}

module_exit(only_exit_module);
