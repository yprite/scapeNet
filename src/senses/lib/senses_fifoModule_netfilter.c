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

static struct kfifo fifo1;		//arp
static struct kfifo fifo;		//traffic and portscan
struct task_struct *t_id1 = 0;
struct task_struct *t_id = 0;
static struct file *filp1;
static struct file *filp;
static int flag = 0;

static void send_myfifo1(char *filename, char *msg);
static void send_myfifo(char *filename, char *msg);
int set_kfifo1(char *msg);
int set_kfifo(char *msg);
int get_kfifo1(char *msg);
int get_kfifo(char *msg);
static int thread_loop1(void *data);
static int thread_loop(void *data);

int __init init_fifo_test(void)
{
	unsigned int i;
	
	filp1 = filp_open("../bin/read_sense", O_WRONLY|O_SYNC, S_IRUSR|S_IWUSR);
	if (IS_ERR(filp1)) {
		const int open_errno = -PTR_ERR(filp1);
        printk("fifo1 open error: %s\n errno=%d", __FUNCTION__, open_errno);
		return 0;
	} else {
		printk("fifo1 open success\n");
	}

	filp = filp_open("../bin/read_sense2", O_WRONLY|O_SYNC, S_IRUSR|S_IWUSR);
	if (IS_ERR(filp)) {
		const int open_errno = -PTR_ERR(filp);
        printk("fifo open error: %s\n errno=%d", __FUNCTION__, open_errno);
		return 0;
	} else {
		printk("fifo open success\n");
	}
	
	printk("fifo1 module insert-----------\n");
	if( kfifo_alloc(&fifo1, FIFOSIZE, GFP_KERNEL) ) {
		printk(KERN_WARNING "fifo1 error kfifo_alloc1 \n");
		return -ENOMEM;
	}

	printk("fifo module insert-----------\n");
	if( kfifo_alloc(&fifo, FIFOSIZE, GFP_KERNEL) ) {
		printk(KERN_WARNING "fifo error kfifo_alloc \n");
		return -ENOMEM;
	}

	printk(KERN_INFO "queue1 size : %u \n", kfifo_size(&fifo1));
	printk(KERN_INFO "queue size : %u \n", kfifo_size(&fifo));

	printk(KERN_INFO "queue1 available : %u\n", kfifo_avail(&fifo1));
	printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));

#if 1
	printk(KERN_INFO "thread_start1\n");
	t_id1 = (struct task_struct *)kthread_run(thread_loop1, NULL, "%s", "create_test1");
	
	printk(KERN_INFO "thread_start\n");
	t_id = (struct task_struct *)kthread_run(thread_loop, NULL, "%s", "create_test");
#endif
	return 0;

}

static int thread_loop1(void *data)
{
	int i;
	char cval[SIZE];
	
	printk(KERN_INFO "stauts1 = %d\n", kthread_should_stop());
	while(!kthread_should_stop()) {
		//udelay((unsigned long) 10000);
		msleep(1);

		memset(cval, 0, sizeof(cval));
		if(get_kfifo1(cval) == 0) {
			continue;
		}
		printk(KERN_INFO "out arp: %s\n", cval);
		printk(KERN_INFO "queue available 1 : %u\n", kfifo_avail(&fifo1));
		send_myfifo1("read_sense", cval);
	}
	printk(KERN_INFO "queue available1 : %u\n", kfifo_avail(&fifo1));
	printk(KERN_INFO "thread_end1\n");

	return 0;
}

static int thread_loop(void *data)
{
	int i;
	char cval[SIZE];
	
	printk(KERN_INFO "stauts = %d\n", kthread_should_stop());
	while(!kthread_should_stop()) {
		//udelay((unsigned long) 10000);
		msleep(1);
		
		if(flag == 1) {
			msleep(3300);
			flag = 0;
			continue;
		}

		memset(cval, 0, sizeof(cval));
		if(get_kfifo(cval) == 0) {
			continue;
		}
		printk(KERN_INFO "out other %s\n", cval);
		printk(KERN_INFO "queue available  : %u\n", kfifo_avail(&fifo));
		send_myfifo("read_sense", cval);
	}
	printk(KERN_INFO "queue available : %u\n", kfifo_avail(&fifo));
	printk(KERN_INFO "thread_end\n");

	return 0;
}



int set_kfifo1(char *msg)
{
	//printk("get msg1 = %s\n", msg);
	if(kfifo_avail(&fifo1) < SIZE)
		return 0;

	kfifo_in(&fifo1, msg, SIZE);

	return 1;
}

int set_kfifo(char *msg)
{
	//printk("get msg = %s\n", msg);
	if(kfifo_avail(&fifo) < SIZE)
		return 0;

	kfifo_in(&fifo, msg, SIZE);

	return 1;
}

int get_kfifo1(char *msg)
{
	if(kfifo_len(&fifo1) <= 0) {
		msg = 0;
		return 0;
	}

	kfifo_out(&fifo1, msg, SIZE);
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
	filp_close(filp1, NULL);  /* filp_close(filp, current->files) ?  */
	if(t_id1) {
		kthread_stop(t_id1);
		t_id1 = 0;
	}

	filp_close(filp, NULL);  /* filp_close(filp, current->files) ?  */
	if(t_id) {
		kthread_stop(t_id);
		t_id = 0;
	}

	kfifo_free(&fifo1);
	kfifo_free(&fifo);

	printk("fifos module removed\n");
}

static void send_myfifo1(char *filename, char *msg)
{
	char bufs[100];
	flag = 1;

	memset(bufs, 0, sizeof(bufs));
	strcpy(bufs, msg);

	/* kernel memory access setting */
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	vfs_write(filp1, bufs, strlen(bufs), &filp1->f_pos);
	set_fs(old_fs);
}

static void send_myfifo(char *filename, char *msg)
{
	char bufs[100];

	memset(bufs, 0, sizeof(bufs));
	strcpy(bufs, msg);

	/* kernel memory access setting */
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	vfs_write(filp, bufs, strlen(bufs), &filp->f_pos);
	set_fs(old_fs);
}


EXPORT_SYMBOL(set_kfifo1);
EXPORT_SYMBOL(set_kfifo);
EXPORT_SYMBOL(send_myfifo);

module_init(init_fifo_test);
module_exit(exit_fifo_test);
MODULE_LICENSE("GPL");