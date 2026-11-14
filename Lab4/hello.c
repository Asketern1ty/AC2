#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_AUTHOR("Viktor Katolikov, IO-43");
MODULE_DESCRIPTION("Lab 4: Hello world with list and ktime");
MODULE_LICENSE("Dual BSD/GPL");

static uint howmany = 1;
module_param(howmany, uint, S_IRUGO);
MODULE_PARM_DESC(howmany, "Number of times to print hello world");

struct hello_data {
    struct list_head list_node;
    ktime_t time;
};

static LIST_HEAD(hello_list_head);

static int __init hello_init(void)
{
    uint i;

    if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
        pr_warn("Warning: the parameter is either 0 or between 5 and 10\n");
    } else if (howmany > 10) {
        pr_err("Error: the parameter is greater than 10\n");
        return -EINVAL;
    }

    for (i = 0; i < howmany; i++) {
        struct hello_data *md = kmalloc(sizeof(*md), GFP_KERNEL);
        if (!md) {
            pr_err("Memory allocation failed\n");
            
            struct hello_data *cur, *tmp;
            list_for_each_entry_safe(cur, tmp, &hello_list_head, list_node) {
                list_del(&cur->list_node);
                kfree(cur);
            }
            return -ENOMEM;
        }
        
        md->time = ktime_get();
        list_add_tail(&md->list_node, &hello_list_head);
        pr_info("Hello, world!\n");
    }

    return 0;
}

static void __exit hello_exit(void)
{
    struct hello_data *md, *tmp;

    list_for_each_entry_safe(md, tmp, &hello_list_head, list_node) {
        pr_info("Event time: %lld ns\n", ktime_to_ns(md->time));
        list_del(&md->list_node);
        kfree(md);
    }
}

module_init(hello_init);
module_exit(hello_exit);
