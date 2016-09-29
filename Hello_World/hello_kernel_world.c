#include <linux/kernel.h>
#include <linux/module.h>

int hello_world_init(void)
{
    printk(KERN_ALERT "Hello Kernel World...!!!");
    return 0;
}

void hello_world_exit(void)
{
    printk(KERN_ALERT "Hello Kernel World...!!!");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
