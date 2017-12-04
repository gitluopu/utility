#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/sched.h>

static int myroutine(void *arg)
{
    do_exit(1);
}

static struct task_struct *ts;
static int __init hello_init(void)
{
    ts=kthread_run(myroutine,NULL,"grocesor");
    return 0;
}


static void __exit  hello_exit(void)
{
}


module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");








































