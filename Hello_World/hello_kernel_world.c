#include <linux/kernel.h>
#include <linux/module.h>

/* "__initdata" can be used to VARIABLES that are used ONLY in init() module
   It is helpful to save memory. Once module is inserted its no longer in memory
*/
__initdata int count;

/* "__init" can be used to FUNCTIONS, that are called ONLY from init() module
   It is helpful to save memory. Once module is inserted its no longer in memory
*/
__init void fun1(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
}

/* Can't use "__init" because it is called in both init() and exit() function
*/
void fun2(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
}

__init int hello_world_init(void)
{
    printk(KERN_ALERT "in %s Hello Kernel World...!!!\n", __FUNCTION__);
    count = 22222222;
    printk(KERN_ALERT "count = %d\n", count);
    fun1();
    fun2();
    return 0;
}

void hello_world_exit(void)
{
    fun2();
    printk(KERN_ALERT "in %s Hello Kernel World...!!!\n", __FUNCTION__);
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
