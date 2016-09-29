#include <linux/kernel.h>
#include <linux/module.h>

int only_init_module(void)
{
    printk(KERN_ERR "in %s\n", __FUNCTION__);
    return 0;
}

module_init(only_init_module);
