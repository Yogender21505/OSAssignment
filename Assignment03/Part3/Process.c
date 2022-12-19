#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/cred.h>
#include<linux/sched/signal.h>
#include<linux/moduleparam.h>

static char *proc="";
module_param(proc,charp,0660);


//--------------task_Struct----------------------------
static void  Required_process(void){
	struct task_struct *task;
	
	for_each_process(task){
		const struct cred *cred= current_cred();
		int ret=strcmp(givenproc,task->comm);
		if (ret==0){
			printk(KERN_INFO "Process Command=%s, pid=%d userid=%d groupid=%d \n", task->comm, task->pid,cred->uid,cred->gid);
			break;
		}
	}
}	

static int __init lkp_init(void)
{
	printk("\n");
	printk(" -------------------===module init===-----------------------\n");
	Required_process();
	return 0;
}

static void __exit lkp_cleanup(void)
{
	printk(" ----------===module exit====-------------\n");
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");
