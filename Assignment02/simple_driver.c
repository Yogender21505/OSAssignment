#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/string.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FOSSEE TEAM");

static int mydevice_open(struct inode *inod,struct file *filp);
static int mydevice_release(struct inode *inode,struct file *filp);
static ssize_t mydevice_read(struct file *filp,const char _user *buff,ssize_t len,loff_t *loff);
static struct class *cl;
static char *ptr = NULL;
static struct cdev my_cdev;
struct file_operation{
     .read=mydevice_read,
     .write=mydevice_write,
     .open=mydevice_open,
     .release=mydevice_release,
};

static int init_function(void){
    printk(KERN_INFO "simple_driver : Inside the intit function of a driver.\n");

    if (alloc_chrdev_region(&device_num,0,1,"my_device")<0){
        printk(KERN_INFO "simple_driver : the device numver allocation fails.\n");
        return -1;
    }
}
static ssize_t mydevice_write(struct file *filp,const char _user *buff, size_t len,loff_t *loff){
    if (len>25){
        pritnk(KERN_INFO "simple_driver : the length is greater than the kernel buffer len.\n");
        return EFAULT;
    }
    if (copy_from_user(ptr,buff,len)){
        return -EFAULT;
    }
    else{
        printk(KERN_INFO "simple_driver : the write to the device successfilly ...\n");
        printk("simple_driver : the data write to device(ptr): %s\n",buff);
    }
}

static ssize_t mydevice_read(struct file *filp,char __user *buff, size_t len, loff_t *loff){
    printk(KERN_INFO "simple_driver : Inside the my_device read function..\n");
    if (copy_to_user(buff,ptr,len)){
        printk(KERN_INFO "simple_driver : the data unable to read.\n");
        return -EFAULT;
    }
    else{
        printk(KERN_INFO "simple_driver : the read from the device successfully..\n");
        printk("simple_driver : the datat read from the deveice(ptr): %s\n",buff);

    }
}
