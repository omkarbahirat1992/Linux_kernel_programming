#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

int chrdev_open(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    return 0;
}

int chrdev_release(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    return 0;
}

ssize_t chrdev_read(struct file *pfile, char __user *puser, size_t psize, loff_t *poffset)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    return 0;
}

ssize_t chrdev_write(struct file *pfile, const char __user *puser, size_t psize, loff_t *poffset)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    return psize;
}

struct file_operations simple_fops = {
    .owner   = THIS_MODULE,
    .open    = chrdev_open,    
    .release = chrdev_release,
    .read    = chrdev_read,
    .write   = chrdev_write
};

__init int simple_char_driver_init(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    register_chrdev(100, "simple_char_driver", &simple_fops);
    return 0;
}

void simple_char_driver_exit(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    unregister_chrdev(100, "simple_char_driver");
}


module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);

MODULE_LICENSE("GPL");
