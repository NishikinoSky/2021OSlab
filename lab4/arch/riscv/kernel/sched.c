#include"put.h"
#include"sched.h"
#include"rand.h"
#define offset (0xffffffe000000000-0x80000000)
#define Kernel_Page            0x80210000
#define LOW_MEMORY             0x80211000
#define PAGE_SIZE              4096UL

struct task_struct *current;
struct task_struct *task[NR_TASKS];
long PRIORITY_INIT_COUNTER[NR_TASKS] = {0,1,2,3,4};
long COUNTER_INIT_COUNTER[NR_TASKS] = {0,1,2,3,4};

extern void init_epc(void);
extern void __switch_to(struct task_struct* current, struct task_struct* next);
extern unsigned int rand();
extern uint64_t cur;

int task_init_done = 0;
void task_init(void)
{
	puts("task init...\n");
    //set task0
        task[0] = (struct task_struct*)(Kernel_Page + offset);
        task[0]->state = TASK_RUNNING;
        task[0]->counter = COUNTER_INIT_COUNTER[0];
        task[0]->priority = PRIORITY_INIT_COUNTER[0];
        task[0]->blocked = 0;
        task[0]->pid = 0;
        task[0]->thread.sp = (unsigned long long) task[0] + TASK_SIZE;

	    asm volatile("la t0, init_epc");
        asm volatile("sd t0, %0"::"m"(task[0]->thread.ra));

    //set other tasks
    for (int i = 1; i <= LAB_TEST_NUM; ++i) {
        /*your code*/
        task[i] = (struct task_struct*)(Kernel_Page + offset + i*TASK_SIZE);
        task[i]->state = TASK_RUNNING;
        task[i]->counter = COUNTER_INIT_COUNTER[i];
        task[i]->priority = PRIORITY_INIT_COUNTER[i];
        task[i]->blocked = 0;
        task[i]->pid = i;
        task[i]->thread.sp = (unsigned long long) task[i] + TASK_SIZE;

	    asm volatile("la t0, init_epc");
	    asm volatile("sd t0, %0"::"m"(task[i]->thread.ra));
	
        puts("[PID = ");
        puti(task[i]->pid);
        puts("] Process Create Successfully! counter = ");
        puti(task[i]->counter);
        puts("\n");
    }
    current = task[0];
    task_init_done = 1;

}

//SJF
void do_timer(void)
{
	if (!task_init_done) return;
    puts("[*PID = ");
    puti(current->pid);
    puts("] Context Calculation: counter = ");
    puti(current->counter);
    puts("\n");
    //current process's counter -1, judge whether to schedule or go on.
    /*your code*/
    current->counter--;
    if (current->counter <= 0) schedule();
}

void schedule(void)
{
	unsigned char next; 
    /*your code*/
    _Bool allzero = 1;
    next = LAB_TEST_NUM;
    for(int i = LAB_TEST_NUM; i > 0; i--){
        if(task[i]->state == TASK_RUNNING){
            if(task[i]->counter > 0) allzero = 0;
            if((task[next]->counter <= 0 && task[i]->counter > 0) || (task[i]->counter > 0 && task[i]->counter < task[next]->counter))
                next = i;
        }
    }

    if(allzero){
        for(int i = 1; i <= LAB_TEST_NUM; i++){
            task[i]->counter = rand();
            puts("[PID = ");
            puti(task[i]->pid);
            puts("] Reset counter = ");
            puti(task[i]->counter);
            puts("\n");
        }
    }

    if(current->pid != task[next]->pid)
    {
        puts("[!] Switch from task ");
        puti(current->pid);
        puts(" [task struct: ");
        putullHex(current);
        puts(", sp: ");
        putullHex(current->thread.sp);
        puts("] to task ");
        puti(task[next]->pid);
        puts(" [task struct: ");
        putullHex(task[next]);
        puts(", sp: ");
        putullHex(task[next]->thread.sp);
        puts("], prio: ");
        puti(task[next]->priority);
        puts(", counter: ");
        puti(task[next]->counter);
        puts("\n");
    }
    switch_to(task[next]);
}


void switch_to(struct task_struct* next)
{
	if (current->pid == next->pid) return;
    else{
	    struct task_struct* n = current;
	    current = next;
        __switch_to(n, next);
    }
}

void dead_loop(void)
{
	while (1) { continue; }
}

