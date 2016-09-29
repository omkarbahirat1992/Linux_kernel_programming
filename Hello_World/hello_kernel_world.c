#include <linux/kernel.h>
#include <linux/module.h>

int hello_world_init(void)
{
    printk(KERN_ERR "in %s Hello Kernel World...!!!", __FUNCTION__);
    return 0;
}

void hello_world_exit(void)
{
    printk(KERN_ALERT "in %s Hello Kernel World...!!!", __FUNCTION__);
}

module_init(hello_world_init);
module_exit(hello_world_exit);
