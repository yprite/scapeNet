#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kfifo.h>

#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
//#include <linux/fcntl.h>
//#include <asm/uaccess.h>
#include <linux/kthread.h>
#include <linux/delay.h>
//#include <linux/completion.h>
//#include <asm/delay.h>
//#include <linux/sched.h>

//#define FIFOSIZE 655360
#define FIFOSIZE 524288
#define SIZE 50

static struct kfifo fifo;
struct task_struct *t_id = 0;
static struct file *filp;

static void send_myfifo(char *filename, char *msg);
int set_kfifo(char *msg);
int get_kfifo(char *msg);
static int thread_loop(void *data);

int __init init_fifo_test(void)
{
	unsigned int i;
	
	filp = filp_open("../bin/read_sense", O_WRONLY, S_IRUSR|S_IWUSR);
	if (IS_ERR(filp)) {
		printk("open error\n");
		const int open_errno = -PTR_ERR(filp);
        printk("open error: %s\n errno=%d", __FUNCTION__, open_errno);
		return 0;
	} else {
		printk("open success\n");
	}
	
	printk("fifo module insert-----------\n");

	if( kfifo_alloc(&fifo, FIFOSIZE, GFP_KERNEL) ) {
		printk(KERN_WARNING "error kfifo_alloc \n");
		return -ENOMEM;
	}

	printk(KERN_INFO "queue size : %u \n", kfifo_size(&fifo));

/*	for(i=0; i<1000; i++) {
		char cval[SIZE];
		memset(cval, 0, sizeof(cval));
		strcpy(cval, "hello my name is khg");
		set_kfifo(cval);
		printk(KERN_INFO "in %s  size: %d\n", cval, strlen(cval));
	}
	*/
	printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));

	//for(i=0; i<12; i++) {
#if 0
	for(i=0; i<100; i++) {

		msleep(10);
		char cval[SIZE];
		memset(cval, 0, sizeof(cval));
		if(get_kfifo(cval) == 0) {
			continue;
		}
		printk(KERN_INFO "out %s\n", cval);
		send_myfifo("read_sense", cval);
	}
	printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));
#endif 
#if 1
	printk(KERN_INFO "thread_start\n");
	t_id = (struct task_struct *)kthread_run(thread_loop, NULL, "%s", "create_test");
	printk(KERN_INFO "thread_next\n");
#endif
	return 0;

}

static int thread_loop(void *data)
{
	int i;
	char cval[SIZE];
	//for(i=0; i<100; i++) {
	
	printk(KERN_INFO "stauts = %d\n", kthread_should_stop());
	while(!kthread_should_stop()) {
		//udelay((unsigned long) 10000);
		msleep(1);

		memset(cval, 0, sizeof(cval));
		if(get_kfifo(cval) == 0) {
			continue;
		}
		printk(KERN_INFO "out %s\n", cval);
		printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));
		send_myfifo("read_sense", cval);
	}
	printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));
	printk(KERN_INFO "thread_end\n");

	return 0;
}



int set_kfifo(char *msg)
{
	printk("get msg = %s\n", msg);
	if(kfifo_avail(&fifo) < SIZE)
		return 0;

	kfifo_in(&fifo, msg, SIZE);

	return 1;
}

int get_kfifo(char *msg)
{
	if(kfifo_len(&fifo) <= 0) {
		msg = 0;
		return 0;
	}

	kfifo_out(&fifo, msg, SIZE);
	return 1;
}



void __exit exit_fifo_test(void)
{
	filp_close(filp, NULL);  /* filp_close(filp, current->files) ?  */
	if(t_id) {
		kthread_stop(t_id);
		t_id = 0;
	}

	kfifo_free(&fifo);
	printk("fifo module removed\n");
}

static void send_myfifo(char *filename, char *msg)
{
//	struct file *filp;
	char bufs[100];

	memset(bufs, 0, sizeof(bufs));
	strcpy(bufs, msg);

	/* kernel memory access setting */
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	/* open a file */
	//filp = filp_open(filename, O_RDWR, 7777);

/*	filp = filp_open(filename, O_RDWR, S_IRUSR|S_IWUSR);
	if (IS_ERR(filp)) {
		printk("open error\n");
		const int open_errno = -PTR_ERR(filp);
        printk("open error: %s\n errno=%d", __FUNCTION__, open_errno);
		return;
	}

	else {
		printk("open success\n");
	}
*/

	/* write example */
	//printk("filp->f_pos = %d\n", (int)filp->f_pos);

	vfs_write(filp, bufs, strlen(bufs), &filp->f_pos);
	//printk("filp->f_pos = %d\n", (int)filp->f_pos);

	//filp_close(filp, NULL);  /* filp_close(filp, current->files) ?  */
	/* restore kernel memory setting */
	set_fs(old_fs);
}


EXPORT_SYMBOL(set_kfifo);
EXPORT_SYMBOL(send_myfifo);

module_init(init_fifo_test);
module_exit(exit_fifo_test);
MODULE_LICENSE("GPL");
