// reset_sys_module.c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>
#include "reset_sys.h"   // protótipo da start_reset_sys()

/* Declare extern implemented in reset_main.cpp */
extern void start_reset_sys(void);

/* Sysfs kobject */
static struct kobject *rs_kobj;

/* sysfs write trigger: echo 1 > /sys/kernel/reset_sys/trigger */
static ssize_t trigger_store(struct kobject *kobj, struct kobj_attribute *attr,
                             const char *buf, size_t count)
{
    if (count > 0 && buf[0] == '1') {
        pr_emerg("[reset_sys_module] sysfs trigger received -> start_reset_sys()\n");
        start_reset_sys();
    }
    return count;
}

static struct kobj_attribute trigger_attr =
    __ATTR(trigger, 0220, NULL, trigger_store);

static int __init reset_sys_module_init(void)
{
    int ret;
    pr_info("reset_sys_module: init\n");
    rs_kobj = kobject_create_and_add("reset_sys", kernel_kobj);
    if (!rs_kobj) {
        pr_err("reset_sys_module: failed to create kobject\n");
        return -ENOMEM;
    }
    ret = sysfs_create_file(rs_kobj, &trigger_attr.attr);
    if (ret) {
        pr_err("reset_sys_module: failed to create sysfs attr\n");
        kobject_put(rs_kobj);
        return ret;
    }
    pr_info("reset_sys_module: loaded (echo 1 > /sys/kernel/reset_sys/trigger to test)\n");
    return 0;
}

static void __exit reset_sys_module_exit(void)
{
    pr_info("reset_sys_module: exit\n");
    if (rs_kobj) {
        sysfs_remove_file(rs_kobj, &trigger_attr.attr);
        kobject_put(rs_kobj);
    }
}

module_init(reset_sys_module_init);
module_exit(reset_sys_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Enzo / ELAT");
MODULE_DESCRIPTION("Wrapper module to export start_reset_sys and provide sysfs trigger");

EXPORT_SYMBOL(start_reset_sys);
