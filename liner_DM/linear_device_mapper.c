/*
This is simple linear device mapper. It reads and writes the data as it is
on a target without any modification.

only .map, .ctr, .dtr function hooks of struct target_type are implemented.
*/


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/device-mapper.h>
#include <linux/bio.h>

struct linear_dm {
    struct dm_dev *dev;
    int start;
};

int linear_dm_ctr(struct dm_target *target_ptr, unsigned int argc, char **argv)
{
    struct linear_dm *l_dm_ptr = NULL;
    int temp;

    printk(KERN_ALERT "in %s\n", __FUNCTION__);

    if (argc != 2) {
        target_ptr->error = "linear-dm: Invalid argument count\n";
        return -EINVAL;
    }  

    if (sscanf(argv[1], "%d", &temp) != 1) {
        target_ptr->error = "linear-dm: Invalid device sector\n";
        return -EINVAL;
    }

    l_dm_ptr = kmalloc(sizeof(*l_dm_ptr), GFP_KERNEL);
    if (l_dm_ptr == NULL){
        target_ptr->error = "linear-dm: Unable to allocate th ememory\n";
        return -ENOMEM;
    }

    l_dm_ptr->start = temp;

    if (dm_get_device(target_ptr, argv[0], dm_table_get_mode(target_ptr->table), &l_dm_ptr->dev)) {
        target_ptr->error = "linear-dm: Unable to get the device\n";
        kfree(l_dm_ptr);
        return -EINVAL;
    }

    target_ptr->private = l_dm_ptr;

    return 0;
}

void linear_dm_dtr(struct dm_target *target_ptr)
{
    struct linear_dm *l_dm_ptr = (struct linear_dm *)target_ptr->private;

    printk(KERN_ALERT "in %s\n", __FUNCTION__);

    dm_put_device(target_ptr, l_dm_ptr->dev);
    kfree(l_dm_ptr);
}

int linear_dm_map(struct dm_target *target_ptr, struct bio *bio_ptr)
{
    struct linear_dm *l_dm_ptr = target_ptr->private;

    printk(KERN_ALERT "in %s\n", __FUNCTION__);

    bio_ptr->bi_bdev = l_dm_ptr->dev->bdev;
    bio_ptr->bi_iter.bi_sector = l_dm_ptr->start + bio_ptr->bi_iter.bi_sector;

    return DM_MAPIO_REMAPPED;
}

struct target_type target_linear = {
    .name = "linear_dm",
    .version = {1, 1, 1},
    .module = THIS_MODULE,
    .ctr = linear_dm_ctr,
    .dtr = linear_dm_dtr,
    .map = linear_dm_map,
};

int linear_dm_init(void)
{
    int ret;
    printk(KERN_ALERT "in %s\n", __FUNCTION__);

    ret = dm_register_target(&target_linear);
    if (ret < 0) {
        printk(KERN_ERR "Unable to register the taget: %d\n", ret);
    }
    return ret;
}

void linear_dm_exit(void)
{
    printk(KERN_ALERT "in %s\n", __FUNCTION__);
    dm_unregister_target(&target_linear);
}

module_init(linear_dm_init);
module_exit(linear_dm_exit);

MODULE_LICENSE("GPL");
