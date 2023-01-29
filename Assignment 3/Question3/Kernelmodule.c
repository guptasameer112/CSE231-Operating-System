# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/sched.h>
# include <linux/init.h>
# include <linux/moduleparam.h>
# include <linux/cred.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sameer");
MODULE_DESCRIPTION("HelloWorld Linux Kernel Module");

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR);
// insmod Kernelmodule.ko pid=1

void printinfo(void);

void printinfo(void)
{
    struct task_struct *task;
    struct pid *pid_struct;

    pid_struct = find_get_pid(pid);
    task = pid_task(pid_struct, pid);

    int pid = task->pid;
    int uid = task->cred->uid.val;
    int gid = task->cred->gid.val;
    char *command_path = task->comm;

    printk(KERN_INFO "Process ID: %d, User ID: %d, Process Group ID: %d, Command Path: %s", pid, uid, gid, command_path);
}

static int __init hello_init(void)
{
    printk(KERN_INFO "Loading module. \n");
    printk(KERN_INFO "Hello World\n");

    printinfo();

    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module. \n");
}

module_init(hello_init);
module_exit(hello_cleanup);
