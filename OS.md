# Operating System

直接参考最后的final tips即可

## 2021-9-18

### Process

- Text section (code)
- Program counter
- Stack (function parameters, local vars, return addresses)
- Data section (global vars)
- Heap (dynamically allocated memory)

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/1.png" alt="1" style="zoom:50%;" />

**程序 & 进程**

进程是程序的一次执行过程，是动态概念。

程序是一组有序的指令集和，是静态概念。

**Process State**: new, running, waiting, ready, terminated

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/2.png" alt="2" style="zoom:33%;" />

#### Process Control Block (PCB)

- Process state (new, ready, ...)
- Program counter (address of next instruction)
- Contents of CPU registers
- CPU scheduling information (priority)
- Memory-management information
- Accounting information (cpu/time used, time limits, process number)
- I/O status information (allocated devices and opened files)

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/3.png" alt="3" style="zoom:50%;" />

**Process Switch**: Save & Load contents of CPU registers

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/4.png" alt="4" style="zoom:40%;" />

#### Process Scheduling Queues

- **Job queue**: set of all processes
- **Ready queue**: set of all processes ready and waiting to execute
- **Device queues**: set of processes waiting for an I/O device

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/5.png" alt="5" style="zoom:40%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/6.png" alt="6" style="zoom:40%;" />

#### Schedulers

- **Long-term scheduler (Job scheduler)**: selects which processes should be brought into memory (the ready queue)

  Frequently invoked -> fast

- **Short-term scheduler (CPU scheduler)**: selects which process should be executed next and allocates CPU

  Infrequently invoked -> slow

Medium Term Scheduling: swap processes out

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/7.png" alt="7" style="zoom:40%;" />

Processes can be described as either:
 ● **I/O-bound process**–spends more time doing I/O than computations, many short CPU bursts

● **CPU-bound process**–spends more time doing computations, few very long CPU bursts

#### Context Switch

Typically takes **milliseconds**

#### Process Creation

**Fork**: system call creates new process

**Exec**: system call used after a **fork** to replace the process’ memory space with a new program

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/8.png" alt="8" style="zoom:35%;" />

```c
int main() {
	pid_t pid;
/* fork another process */
	pid = fork();
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
	exit(-1); }
	else if (pid == 0) { /* child process */
		execlp("/bin/ls", "ls", NULL); }
	else { 
    /*pid > 0 because parent will get the returned pid of child*/
    /* parent process */
    /* parent will wait for the child to complete */
		wait (NULL);
		printf ("Child Complete"); exit(0);
	}
}
```

#### Interprocess Communication (IPC)

Models for IPC: **message passing** and **shared memory**

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021918/9.png" alt="9" style="zoom:40%;" />



#### Synchronization

**Blocking**

#### Client-Server Communication

**Sockets**: concatenation of IP address and port

- The socket **161.25.19.8:1625** refers to port **1625** on host **161.25.19.8**
- Communication consists between a pair of sockets

**Remote Procedure Calls**: RPC 

Client-side: **Stubs**

## 2021-9-22

### Threads

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/1.png" alt="1" style="zoom:40%;" />

Threads of one process can easily share data, code and file; but have different registers and stacks.

Processes are typically independent, while threads exist as subsets of a process.

#### Multithreading Models

OS kernel only calls kernel threads and then kernel threads call user threads needed.

Kernel threads <> User threads

**Many-to-One**: Many user-level threads mapped to single kernel thread.

(User threads can come from different processes)

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/2.png" alt="2" style="zoom:40%;" />

**One-to-One**: Each user-level thread maps to kernel thread

Problem: kernel threads are not sufficient.

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/3.png" alt="3" style="zoom:40%;" />

**Many-to-Many**: Many user-level threads map to many kernel threads

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/4.png" alt="4" style="zoom:40%;" />

**Two-level**: similiar to M2M but allows a user thread to be bound to a singal kernel thread.

Allows some important user threads to get more resource.

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/5.png" alt="5" style="zoom:40%;" />

#### Thread Issues

**fork() & exec()**

Some unix systems have two kinds of fork, allowing fork() to duplicate both the calling thread and all threads.

But exec() will replace the entire process. (because the code has changed)

**Thread Cancellation**

- **Asynchronous cancellation **terminates the target thread immediately
- **Deferred cancellation** allows the target thread to periodically check via a flag if it should be cancelled

**Thread Pools**

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/6.png" alt="6" style="zoom:45%;" />

since the number of threads is fixed, it's unnecessary to create threads when user needs.

**Thread Specific Data**

Allows each thread to have its own copy of data

#### Scheduler Activations

LWP (**Light-weight process**) is a **virtual processor** attached to kernel thread, choosing user threads.

LWP is a struct, not a process.

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021922/7.png" alt="7" style="zoom:50%;" />



## 2021-9-27

### CPU Scheduling

CPU Scheduling decisions happens when a process:

**nopreemptive**

1. Switch from running to waiting
2. Terminates

**preemptive**

1. Switch from running to ready state
2. Switch from waiting to ready

#### Dispatcher

gives control of the CPU to the process selected by the short-term scheduler.

#### Scheduling Criteria

- CPU utilization: keep the CPU busy
- Throughput: complete more processes per time unit
- Turnaround time: amount of time to execute a particular process
- Waiting time: amount of time a process waiting in the ready queue
- Response time: amount of time it takes from starting to producing the first response

#### First-Come, First-Served (FCFS) Scheduling

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021927/1.png" style="zoom:40%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021927/2.png" style="zoom:40%;" />

#### Shortest-Job-First (SJF) Scheduling

Associate with each process the length of its next CPU burst.

Two schemes:

- nonpreemptive – once CPU given to the process it cannot be preempted until completes its CPU burst
- preemptive–if a new process arrives with CPU burst length less than remaining time of current executing process, preempt. This scheme is known as the **Shortest-Remaining-Time-First (SRTF)**

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021927/3.png" style="zoom:40%;" />

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021927/4.png" style="zoom:40%;" />

#### Next CPU Burst

using the length of previous CPU bursts, using exponential averaging

- $t_{n}$ = actual length of $n$th CPU burst

- $\tau_{n+1}$ = predicted value for the next CPU burst
- $\alpha, 0 \le \alpha \le 1$
- Define: $\tau_{n+1} = \alpha t_{n} + (1-\alpha)\tau_{n}$

#### Round Robin (RR) Scheduling

Each process gets a small unit of CPU time (time quantum), usually 10-100 milliseconds. After this time has elapsed, the process is preempted and added to the end of the ready queue.

Less response time, more waiting time.

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021927/5.png" style="zoom:40%;" />

#### Multilevel Queue

- foreground – RR
- background – FCFS

#### Multiple-Processor Scheduling

- Asymmetric multiprocessing – only one processor accesses the system data structures, alleviating the need for data sharing; others execute only user code. (ARM)
- Symmetric multiprocessing (SMP) – each processor is self-scheduling. Multiple processors might access and update a common data structure. (Intel)

#### Real-Time Scheduling

- Hard – missing a deadline is a total system failure.
- Firm – infrequent deadline misses are tolerable, but may degrade the system's quality of service. The usefulness of a result is zero after its deadline.
- Soft – the usefulness of a result degrades after its deadline, thereby degrading the system's quality of service.



## 2021-9-29

### Process Synchronization

#### Critical-section problem

```c
do {
  #Entry section
  Critical section ; // where processes will race
  #Exit section
  Remainder section ;
}while (TRUE);
```

**Solution**

- **Mutual Exclusion** - If process **Pi** is executing in its critical section, then no other processes can be executing in their critical sections
- **Progress** - If no process is executing in its critical section and there exist some processes that wish to enter their critical section, then the selection of the processes that will enter the critical section next cannot be postponed indefinitely
- **Bounded Waiting** - A bound must exist on the number of times that other processes are allowed to enter their critical sections after a process has made a request to enter its critical section and before that request is granted

#### Peterson's Solution

Assume that the **LOAD** and **STORE** instructions are **atomic**.

Two variables:

- int turn; // indicates the progress's turn to enter critical section
- Boolean flag[2]; // indicates if a process is ready to enter, `flag[i] == true` implies process Pi is ready.

**Algorithm for process Pi**

```c
while (true){
  flag[i] = TRUE;
  turn = j;
  while (flag[j] && turn == j);
  	Critical section;
  flag[i] = FALSE;
  	Remainder section;
}
```

**why `turn = j` instead of `turn = i`?**

If two processes are running the statement simultaneously, only one will last.

<img src="/Users/skyyyy/Documents/2021_AUT&WIN/OS/2021929/1.png" style="zoom:40%;" />

#### Synchronization Hardware

Atomatic hardware instructions -> non-interruptable

**Atomatic instructions**:

Busy waiting costs too much time!

- **TestAndSet** Instruction

  ```c
  boolean TestAndSet (boolean *target) {
  	boolean rv = *target; 
  	*target = TRUE; 
  	return rv; // return the original value and set the value as true
  }
  ```

  **Solution**

  Shared boolean variable lock., initialized to false.

  ```c
  while (true) {
  	while ( TestAndSet (&lock)); // 
  	Critical section;
  	lock = FALSE; // the first process finishes critical section
  	Remainder section;
  }
  ```

  

- **Swap** Instruction

  ```c
  void Swap (boolean *a, boolean *b) {
  	boolean temp = *a;
    *a = *b;
  	*b = temp:
  }
  ```

  **Solution**

  Shared Boolean variable lock initialized to FALSE; Each process has a local Boolean variable key.

  ```c
  while (true) {
  	key = TRUE;
  	while ( key == TRUE)
  		Swap (&lock, &key ); 
    Critical section;
  	lock = FALSE;
  	Remainder section;
  }
  ```


#### Semaphore

Semaphore **S** – integer variable

Two atomic standard operations modify S: **wait()** and **signal()**

( originally called P() and V() )

```c
wait (S) {
	while S <= 0
	; // no-op
	S--;
}
signal (S) {
S++; 
}
```

**Counting semaphore** – integer value can range over an unrestricted domain

**Binary semaphore** – integer value can range only between 0 and 1; can be simpler to implement - Also known as **mutex locks**

#### Semaphore Implementation with no Busy waiting

```c
value (of type integer)
pointer to a linked-list of PCBs. 
Typedef struct{
	Int value;
	Struct process *list; 
} semaphone;
```

Two operations (provided as basic system calls):

-  **block** – place the process invoking the operation on the appropriate waiting queue.
-   **wakeup** – remove one of processes in the waiting queue and place it in the ready queue.

```c
wait (S){ 
	value--;
	if (value < 0) {
		add this process to waiting queue
		block(); }
}
```

```c
Signal (S){ 
	value++;
	if (value <= 0) {
		remove a process P from the waiting queue
		wakeup(P); }
}
```

#### Deadlock and Starvation

**Deadlock** – two or more processes are waiting indefinitely for an event that can be caused by only one of the waiting processes

**Starvation** – indefinite blocking. A process may never be removed from the semaphore queue in which it is suspended.

#### Classical Problems of Synchronization

**Bounded-Buffer Problem**

- Semaphore mutex initialized to the value 1

- **Producer**: Semaphore full initialized to the value 0, counting full items

  ```c
  while (true) {
  // produce an item 
    wait (empty);
  	wait (mutex);
  // add the item to the buffer
  	signal (mutex);
  	signal (full); 
  }
  ```

- **Consumer**: Semaphore empty initialized to the value N, counting empty items. 

  ```c
  while (true) { 
    wait (full);
  	wait (mutex);
  // remove an item from buffer
  	signal (mutex); 
    signal (empty);
  // consume the removed item
  }
  ```



**Readers-Writers Problem**

A data set is shared among a number of concurrent processes

●  Readers – only read the data set; they do not perform any updates

●  Writers – can both read and write.

Shared Data

●  Data set

●  Semaphore mutex initialized to 1, to ensure mutual exclusion when readcount is updated.

●  Semaphore wrt initialized to 1.

●  Integer readcount initialized to 0.

Writer process

```c
while (true) {
	wait (wrt) ;
// writing is performed
	signal (wrt) ; 
}
```

Reader process

```c

while (true) {
	wait (mutex) ;
	readcount ++ ;
	if (readcount == 1) wait (wrt) ; 
  signal (mutex)
// reading is performed
	wait (mutex) ;
	readcount - - ;
	if (readcount == 0) signal (wrt) ; 
  signal (mutex) ;
}
```



**Dining-Philosophers Problem**

Shared data

●  Bowl of rice (data set)

●  Semaphore chopstick [5] initialized to 1

The structure of Philosopher i:

```c
While (true) {
	wait ( chopstick[i] );
	wait ( chopStick[ (i + 1) % 5] ); 
// eat
	signal ( chopstick[i] );
	signal (chopstick[ (i + 1) % 5] );
// think
}
```

Deadlock

## 2021-10-11

Database



## 2021-10-13

### Deadlocks

Deadlock can arise if four conditions hold **simultaneously**:

- Mutual exclusion: 排他性，同一个资源不能被多个进程得到
- hold and wait: 一个进程需要多个资源，有些资源已经得到，另一些需要等待
- no preemption: 非抢占式
- circular wait: 循环等待

资源分配图里没有环 必然没有死锁

资源分配图里有环 

- if only one instance per resource type, then deadlock.
- if several instances per resource type, possibility of deadlock.



## 2021-10-18

### Linux进程管理



## 2021-10-20 10-25

### Memory

- Effective Access Time

## 2021-10-27

分段机制/虚拟内存

Demanding Paging 按需分页机制

## 2021-11-1

swap分区

## 2021-11-10

File

- Contiguous logical address space

Directory Structure 目录结构

- 目录自身也是文件
- 作用类似索引









# Final Tips

[王道](https://wizardforcel.gitbooks.io/wangdaokaoyan-os/content/index.html)

[易百](https://www.yiibai.com/os)

### *fork() & exec()*

[参考](https://blog.csdn.net/Helloo_jerry/article/details/77336724)

### IPC（interprocess commuication）进程间通信

[IPC](https://www.jianshu.com/p/c1015f5ffa74)

### *producer-consumer* problem 生产者消费者问题

producer进程每次生产一个产品（data）放入buffer，consumer进程每次从buffer中取出一个产品并使用。

buffer未满：生产者放入，否则wait

buffer非空：消费者取出，否则wait

**同步关系**：生产者与消费者在以上条件下需要wait

**互斥关系**：进程对buffer进行操作时需要互斥

**信号量**

信号量只能由PV操作改变，P为请求资源（S = S - 1），V为释放资源（S = S + 1）

**P操作即wait()，V操作即signal()**

```c
semaphore mutex = 1; //互斥信号量，在同一进程中进行一对PV操作实现互斥
semaphore empty = n; //同步信号量，表示空闲缓冲区数量（缓冲区初始大小为n）
semaphore full = 0; //同步信号量，表示产品数量（非空缓冲区数量）
```

```c
producer(){
    while(1){
      生成一个产品;
      P(empty); //消耗一个空闲缓冲区
      P(mutex);
      把产品放入缓冲区;
      V(mutex);
      V(full)   //增加一个产品
    }
}
```

```c
consumer(){
    while(1){
      P(full);   //消耗一个产品
      P(mutex);
      从缓冲区取出一个产品;
      V(mutex);
      V(empty);  //增加一个空闲缓冲区
      使用产品;
    }
}
```

**实现互斥的P操作一定要在实现同步的P操作之后，但两个V操作可以交换顺序**

[实例](https://zhuanlan.zhihu.com/p/61326272)

### CPU调度

[参考](https://www.jianshu.com/p/65360b500ad9)

CPU利用率（CPU utilization）。CPU的利用率就是非空闲进程占用时间的比例，即CPU执行非空闲进程的时间/ CPU总的执行时间。

吞吐率（Throughput） — 单位时间内完成执行的进程数

周转时间（Turnaround time） — 执行某一进程所耗用的CPU累积时间（进程进入就绪队列开始到拿到CPU执行结束为止的累积时间，其间有可能存在时间片到了或者高优先级抢占CPU的情况）

等待时间（Waiting time） — 某一进程等待在就绪队列里面的累积时间（不包括CPU执行时间）

响应时间（Response time） — 某一进程从发出调度请求，到其开始得到CPU调度器响应，其间所经历的时间。

***waiting time = turnaround time - burst time（等待时间 = 周转时间 - 运行时间）***

#### CPU调度器（Dispatcher）：

**CPU调度器决定了将CPU分配给谁。后续操作就是，CPU分配器将CPU控制权移交给该进程**。
操作内容通常包括：

- 上下文切换（switching context）
- 从内核态（kernel mode）转移至用户态（user mode）
- 跳转至用户程序中PC寄存器所指示的位置

#### a. First-Come,First-Served Scheduling（FCFS）调度算法（）

#### b. Shortest-Job-First（SJF）调度算法（最短作业优先算法）

- 非抢占式
- 抢占式：后来的进程运行时间会与当前进程的剩余运行时间比较

缺陷在于无法精确得到进程所需的时间

##### **预估cpu burst**

根据之前的cpu bursts进行预估

$t_n = $ actual length of $n^{th}$ CPU burst

$\tau_{n+1} = $ Predicted value for the next CPU burst

$\alpha, 0\le\alpha\le1$

**Define $\tau_{n+1} = \alpha t_n + (1 - \alpha )\tau_n$**

#### c. Priority Scheduling（优先权法）

优先数（priority number）越小，优先级越高

- 当优先权定义为进程“需要的CPU时间”时，SJF算法就是优先权法。

缺陷：starvation 进程饥饿——优先权较低的就绪进程可能永远得不到CPU

解决：aging思想——就绪进程等在就绪队列里的时间，折算叠加到进程优先权。因此，等待在就绪队列里的进程，其优先权单调递增。

#### d. Round Robin (RR) （轮转法）

- 每个就绪进程获得一小段CPU时间（**时间片，time quantum**），通常10ms - 100ms
- 时间片用毕，这个进程被迫交出CPU，重新挂回到 **就绪队列**
- 假设n个就绪进程，时间片q，每个就绪进程得到1/n的CPU时间。任何就绪进程最多等待（n-1）q单位时间。

缺陷在于如果上下文切换过于频繁会浪费时间，建议时间片大于等于6

#### 多层队列（Multilevel Queue）

### 进程同步 **Process Synchronization**

```c
do{
  entry section//进入区。为了进入临界区使用临界资源，在进入去要检查可否进入临界区。
  critical section;//临界区。进程中访问临界资源的那段代码。
  exit section;//退出区。将正在访问临界区的标志清除。
  remainder section;//剩余区。代码中的其余部分。
}while(true);
```

#### Bernstein条件 & 前趋图

[参考](https://blog.csdn.net/KoalaZB/article/details/52713489)

#### a. Peterson算法

```c
Pi:
flag[i] = true; turn = j;
while (flag[j] && turn == j);
critical section;// 访问临界区
flag[i] = false;
remainder section;// 剩余区
 
Pj:
flag[j] = true; turn = i;
while (flag[i] && turn == i);
critical sectionl// 访问临界区
flag[j] = false;
remainder section;// 剩余区
```

`flag[i]==ture`则Pi进程想要进入临界区（有访问意愿）

turn用来实现对想要进入临界区的进程的排序（先提出申请的进程的turn会被后提出申请的进程 的turn覆盖）（`turn==i`则Pj在前，`turn==j`则Pi在前）

**因此不能交换flag和turn，如果交换位置，意味着在没有访问意愿的情况下先发送访问请求**

若Pi和Pj都想进入临界区，i先提出申请，j后提出申请，进入while循环判定时`turn==i`（Pi执行`turn=j`在前，Pj执行`turn=i`在后，所以while循环中的`turn==i`）；先提出申请的进程先进入临界区；Pi走到while循环，此时`flag[j]==true`，`turn==i`，不满足循环条件，跳出（若是Pj不想进入临界区没有提出申请，那么`flag[j]==false`，更不满足循环条件），Pi就可以继续进入critical section；Pj走到while循环，但是因为此时`flag[i]==ture`且`turn==i`，Pj陷入while循环中无法进入critical section，Pj需要一直等到Pi退出临界区时置`flag[i]==false`才能跳出循环，进入临界区；

#### b. 硬件同步

[参考](https://blog.csdn.net/weixin_44075132/article/details/116503739)

原子性

Lock为每个临界资源设置的共享布尔变量，true表示正在被占用，false表示没被占用.

##### 1. TSL指令（TestandSet Lock）

```c
/*
* 布尔型共享变量lock 表示当前临界区是否被加锁
* true表示已加锁，false 表示未加锁
*/
bool TestAndTest(bool *lock){
	bool old;
    old = *lock;
    *lock = true;
    return old;
}
/* 以下是使用TSL指令实现互斥的算法逻辑 */
while(TestAndSet(&lock));/*"上锁" 并 "检查" */
//临界区代码...
lock = false;
//剩余区代码...
```

若刚开始lock 是false，则 TSL 返回的old 值为false，while 循环条件不满足，直接跳过循环，进入临界区。若刚开始lock 是true，则执行 TLS 后old 返回的值为true，while 循环条件满足，会一直循环，直到当前访问临界区的进程在退出区进行“解锁”。

##### 2. Swap（XCHG）指令

```c
/* Swap 指令的作用是交换两个变量的值 */
Swap (bool *a ,bool *b){
	bool temp = *a;
    *a = *b;
    *b = temp;
}

bool old = true;
while( old == true )
    Swap(&lock, &old);
//临界区代码...
lock = false;
//剩余区代码...
```

先记录下此时临界区是否已经被上锁（记录在old量上），再将上锁标记lock 设置为true，最后检查 old，如果 old 为false 则说明之前没有别的进程对临界区上锁，则可跳出循环，进入临界区。



以上解决方法均无法实现**让权等待**（当进程不能进入自己的临界区时，应立即释放处理机，以免进程陷入“忙等”状态。）

忙等：当一个进程正处在某临界区内，任何试图进入其临界区的进程都必须进入代码连续循环，陷入忙等状态。连续测试一个变量直到某个值出现为止，称为忙等。

死等：进程在有限时间内根本不能进入临界区，而一直在尝试进入，陷入一种无结果的等待状态。

#### c. **Semaphore** 信号量机制

S: wait() and signal() (P() and V())

##### 1. 整型信号量

```c
int S = 1;
void wait(int S){
  while(S <= 0); //若资源不够则会忙等
  S --;
}
void signal(int S){
  S ++;
}

Process P0:
wait(S);
//临界区code
signal(S);
//剩余区code
```

##### 2. 记录型信号量

**不会造成忙等问题**

```c
typedef struct{
  int value; //剩余资源数
  struct process *L; //等待队列
} semaphore；
  
void wait(semaphore S){
  S.value --;
  if(S.value < 0) block(S.L); 
  //剩余资源不够，使用block原语使进程进入阻塞态并挂到等待队列中
}

void signal(semaphore S){
  S.value ++;
  if (S.value <= 0) wakeup(S.L);
//释放资源后从等待队列中唤醒一个进程
}
```

信号量的值如果小于0，说明此时有进程在等待这种资源

##### 信号量机制实现进程同步

让各并发进程按要求有序地推进

1. 分析什么地方需要实现“同步关系”，即必须保证“一前一后”执行的两个操作（或两句代码）
2. 设置同步信号量S, 初始为0
3. 在“前操作”之后执行V(S)
4. 在“后操作”之前执行P(S)

#### d. 经典同步问题

##### 1. Bounded-Buffer Problem

即生产者消费者问题

##### 2. 吸烟者问题

即“可以生产多个产品的单生产者”问题

假设一个系统有三个抽烟者进程和一个供应者进程。每个抽烟者不停地卷烟并抽掉它，但是要卷起并抽掉一支烟，抽烟者需要有三种材料：烟草、纸和胶水。

三个抽烟者中，第一个拥有烟草、第二个拥有纸、第三个拥有胶水。

供应者进程无限地提供三种材料，供应者每次将两种材料放桌子上，拥有剩下那种材料的抽烟者卷一根烟并抽掉它，并给供应者进程一个信号告诉完成了，供应者就会放另外两种材料再桌上，这个过程一直重复（让三个抽烟者轮流地抽烟）

```c
semaphore offer1 = 0; // 桌上组合一的数量
semaphore offer2 = 0; // 桌上组合二的数量
semaphore offer3 = 0; // 桌上组合三的数量
semaphore finish = 0; // 抽烟是否完成
int i = 0; // 用于实现“三个抽烟者轮流抽烟”

provider() {
	while(1){
		if(i == 0) {
			将组合一放桌上 ;
			V(offer1);
		} else if(i == 1){
			将组合二放桌上 ;
			V(offer2);
		} else if(i == 2){
			将组合三放桌上 ;
			V(offer3);
		}
		i = (i+1)%3;
    //若要随机，则改成 i = rand()%3;
		P(finish);
	}
}

smoker1(){
  while(1){
    P(offer1);
    拿材料，抽烟；
    V(finish);
  }
}
//其余2人同理
```

##### 3. Readers-Writers Problem 读者-写者问题

有读者和写者两组并发进程，共享一个文件，当两个或两个以上的读进程同时访问共享数据时不会产生副作用（因为读者不会改变数据），但若某个写进程和其他进程（读进程或写进程）同时访问共享数据时则可能导致数据不一致的错误。

两类进程：写进程、读进程
互斥关系：写进程—写进程、写进程—读进程。读进程与读进程不存在互斥问题。

```c
semaphore rw=1; // 用于实现对共享文件的互斥访问
int count = 0; // 记录当前有几个读进程在访问文件
semaphore mutex = 1;// 用于保证对count变量的互斥访问

writer(){
  while(1){
    P(rw); //写之前加锁
    写文件;
    V(rw); //写后解锁
  }
}

reader(){
  while(1){
    P(mutex); //各进程互斥访问count
    if(count == 0) P(rw); //第一个读进程负责读之前加锁
    count ++;
    V(mutex);
    读文件;
    P(mutex);
    count --;
    if(count == 0) V(rw); //最后一个读进程负责读完解锁
    V(mutex);
  }
}
```

##### 4. Dining-Philosophers Problem 哲学家就餐问题

一张圆桌上坐着5名哲学家，每两个哲学家之间的桌上摆一根筷子，桌子的中间是一碗米饭。哲学家们倾注毕生的精力用于思考和进餐，哲学家在思考时，并不影响他人。只有当哲学家饥饿时，才试图拿起左、右两根筷子（一根一根地拿起）。如果筷子已在他人手上，则需等待。饥饿的哲学家只有同时拿起两根筷子才可以开始进餐，当进餐完毕后，放下筷子继续思考。

系统中有5个哲学家进程，5位哲学家与左右邻居对其中间筷子的访问是互斥关系。每个哲学家进程需要同时持有两个临界资源才能开始吃饭。

信号量设置：定义互斥信号量数组 chopstick[5]={1,1,1,1,1} 用于实现对5个筷子的互斥访问。并对哲学家按0~4编号，哲学家 i 左边的筷子编号为i，右边的筷子编号为 (i+1)%5。

若5个哲学家进程并发拿起左边的筷子，则会发生死锁。

可设置限制条件：仅当一个哲学家左右两支筷子都可用时才允许他抓起筷子。

```c
semaphore chopstick[5]={1,1,1,1,1};
semaphore mutex = 1; // 互斥地取筷子

Pi (){ //i号哲学家的进程
	while(1){
    P(mutex);
		P(chopstick[i]); // 拿左
		P(chopstick[(i+1)%5]); // 拿右
		V(mutex);
		吃饭…
		V(chopstick[i]); // 放左
		V(chopstick[(i+1)%5]); // 放右
		思考…
	}
}
```

#### e. Monitors 管程机制

信号量机制可能在特定执行顺序下出现错误，难以检测，由此引入管程机制。

条件变量`condition x, y;`

只有操作 wait() 和 signal() 可以调用。操作 `x.wait();` 意味着调用这一操作的进程会被挂起，直到另一进程调用 `x.signal();`

[进程同步问题](https://www.cnblogs.com/wkfvawl/p/11557982.html)

### 死锁 Deadlock

#### a. 死锁产生的必要条件：

- 互斥 **Mutual exclusion**：多进程共享的资源具有互斥特性，一次只能由一个进程使用。如果另一个进程申请资源，那么申请进程必须等待，直到该资源被释放。
- 不剥夺 **No preemption**：进程所获得资源在未使用完毕之前，不能被强行夺走，只能由进程自己释放。
- 占有并等待 **Hold and wait**（部分分配）：进程每次申请它所需要的一部分资源，在等待新资源的同时，进程继续占用已分配到的资源。
- 环路条件 **Circular wait**（循环等待）：有一种循环链，链中每一个进程已获得的资源同时被链中下一个进程所请求。

（prevention）避免产生环路：实行资源有序分配策略。**采用这种策略，即把资源事先分类编号，按号分配，使进程在申请，占用资源时不会形成环路。**所有进程对资源的请求必须严格按资源序号递增的顺序提出。进程占用了小号资源，才能申请大号资源，就不会产生环路，从而预防了死锁。

#### b. 避免死锁（avoidance）

##### 1. Safe State 安全状态

所谓系统是安全的，是指系统中的所有进程能够按照某一种次序分配资源，并且依次地运行完毕，这种进程序列{P1，P2，...，Pn}就是**安全序列**。

对任意 i 和所有 j < i，所有Pj进程资源之和以及当前剩余的资源能满足Pi的运行。

##### 2. Resource-Allocation Graph 资源分配图

[参考](https://blog.csdn.net/nima1994/article/details/65657250)

##### 3. Banker's Algorithm 银行家算法

[参考](https://www.cnblogs.com/wkfvawl/p/11929508.html)

n为进程总数，m资源类别数目

可用资源向量available：`available[j] = k`表示当前j类资源最大可利用数目为k

最大需求矩阵max（$n \times m$）：`max[i, j] = k`表示进程Pi可最多需要申请j类资源数目为k

分配矩阵allocation（$n \times m$）：`allocation[i, j] = k`表示进程Pi当前占有j类资源数目为k

需求矩阵need（$n \times m$）：`need[i, j] = k`表示进程Pi还需要j类资源数目为k

请求向量request：$Request_i[j] = k$表示进程Pi当前对j类资源的申请数目为k

**`need[i, j] = max[i, j] - allocation[i, j]`**

**银行家算法描述如下：**

设P$_i$向系统提出request$_i$资源请求

1. 若request$_i$ > need$_i$，则P$_i$出错；
2. 若request$_i$ > available，则P$_i$阻塞；
3. 试做：available - request$_i$; allocation + request$_i$; need$_i$ - request$_i$; 检查安全性，若安全则分配，否则P$_i$阻塞。（寻找安全序列）

**安全性算法描述如下：**

1. Work = Avaliable

   Finish [i] = false for i = 0, 1, .... , n-1

2. 若不存在i同时满足Finish[i] == false 和 Need$_i \leq$ Work，则跳转到第4步（即没找到可加入安全序列的进程）

3. Work = Work + Allocation$_i$ （假设该进程不久后归还资源）

   Finish[i] = true

   跳转到第2步

4. 如果对所有i都满足Finish[i] == true，则系统在安全态

#### c. 发现死锁（deadlock detection）

##### wait-for graph

Pi →Pj if Pi is waiting for Pj.

根据Resource-Allocation Graph化简

##### detection算法

1. Work = Avaliable

   if Allocation$_i \neq 0$ ，Finish [i] = false for i = 0, 1, .... , n-1

   otherwise Finish[i] = true

2. 若不存在i同时满足Finish[i] == false 和 Request$_i \leq$ Work，则跳转到第4步

3. Work = Work + Allocation$_i$ 

   Finish[i] = true

   跳转到第2步

4. 如果对某些i满足Finish[i] == false，那么系统在死锁状态。

#### d. 死锁恢复

1. process termination
2. resource preemption

### 内存管理 Memory

[进程创建过程](https://wizardforcel.gitbooks.io/wangdaokaoyan-os/content/13.html)

逻辑地址和物理地址在编译时刻、装入（绝对装入）时刻一致；在执行时刻不同

#### Memory-Management Unit (MMU)

把逻辑地址映射成物理地址

relocation register（重定位寄存器）：含最小的物理地址值

界地址寄存器：含最大逻辑地址值

MMU将逻辑地址值与重定位寄存器值相加得到物理地址值

MMU使得程序只需要逻辑地址连续就可以运行，不必物理地址连续

#### 覆盖与交换技术

覆盖：早期计算机系统把用户空间分成一个固定区和若干个覆盖区。将经常活跃的部分放在固定区，其余部分按调用关系分段。首先将那些将要访问的段放入覆盖区，其他段放在外存中，在需要调用时，系统再将其掉入覆盖区，替换其中原有的段。

交换：把处于等待状态（或在CPU调度原则下被剥夺运行权利）的进程从内存移到辅存（backing store），把内存空间腾出来，这一过程又叫换出；把准备好竞争CPU运行的进程从辅存移到内存，这一过程又称为换入。

为了有效使用CPU，需要每个进程的执行时间比交换时间长，而影响交换时间的主要是转移时间。转移时间与所见换的内存空间成正比。

#### contiguous allocation 连续分配管理

- Base register 包含最小物理地址值
- Limit register 包含最大逻辑地址值

物理地址不能超过base+limit

##### Multiple-partition allocation 多区分配算法

1）首次适应算法（first-fit）：空闲分区以地址递增的次序链接。分配内存时顺序查找，找到大小能满足要求的第一个空闲分区（hole）。

2）最佳适应算法（best-fit）：空闲分区按容量递增形成分区链，找到第一个能满足要求的空闲分区。

3）最坏适应算法（worst-fit）：最大适应算法，空闲分区以容量递减次序链接。找到第一个能满足要求的空闲分区，也就是挑选最大的分区。

4）临近适应算法（next-fit）：又称循环首次适应算法，由首次适应算法演变而成。不同之处是分配内存时从此查找结束的位置开始继续查找。

first-fit算法往往最简单高效，但会在低地址部分产生很多碎片

next-fit算法则相反，会在内存末尾产生很多碎片

best-fit算法性能较差，每次分配产生最小的内存块，产生最多碎片

worst-fit产生碎片较少，但会很快没有大块可用，性能很差

空闲分区可作为链表/数组以查找（unix初版本）

##### Fragmentation 碎片

**外部碎片（External Fragmentation）**：指还没有分配出去，但是由于大小太小而无法分配给申请空间的新进程的内存空间空闲块。（即全部空闲空间满足需求，但不连续）

**内部碎片（Internal Fragmentation）**：已经被分配出去的的但大于请求所需的内存空间（allocated memory may be slightly larger than requested memory，直到内存结束或者释放才能利用）

固定分区会产生内部碎片，动态分区会产生外部碎片

可利用**compaction**（possible only if relocation is dynamic, and is done at execution time）或者**非连续分配管理**减少外部碎片。

#### non-contiguous allocation 非连续分配管理

##### Paging 分页

- Divide physical memory into fixed-sized blocks called **frames**（页框）
- Divide logical memory（进程的逻辑地址） into blocks of same size called **pages**

Page是逻辑地址上的基本单位，Frame是物理地址上的基本单位，两者通过MMU形成映射关系。

**Address Translation Schema 地址变换机构**

页表记录了逻辑地址上的一页对应了物理地址上的一帧。把逻辑地址输入进MMU，同时给MMU载入页表。

```c
			logical address														physical address
|-- (m-n) -- |  -- n --  |							|-- (m-n) -- |  -- n --  |
|     p      |     d     | ----MMU----> |     f      |     d     |
| page number|page offset|	page table  |frame number|page offset|
```

通过**页号p**在**页表**（page table）中找到对应的**物理地址块号**（frame number），再根据偏移量d得到最终物理地址。（如果页号大于或等于页表长度，则表示地址越界并中断）

进程向操作系统申请内存后，进入等待队列。然后系统通过算法，根据该进程的页（Page），从free pool里面分配一定数目的帧（Free Frame），生成页表存储到PCB，进程变为ready态。

**Hardware Implementation of Page Table**

- **Page-table base register (PTBR)** 指向 page table
- **Page-table length register (PTLR)** 包含page table大小

在这个模型中需要访问两次内存，第一次得到页表，第二次得到真实物理地址（two-memory-access problem）。这个问题可以利用**TLBs**（**translation look-aside buffers** / **associative memory** 转换旁视缓冲，即快表）解决。TLB就是页表的Cache，其中存储了当前最可能被访问到的页表项，其内容是部分页表项的一个副本。

**Effective Access Time （EAT）有效访问时间**

一次内存访问时间为 $t$

查找快表所需时间 $\varepsilon$

快表命中率（hit ratio） = $\alpha$

$EAT = (t + \varepsilon) \alpha + (2t + \varepsilon)(1 - \alpha) = 2t + \varepsilon - t\alpha$

**valid-invalid bit**

表示page是否在进程的逻辑地址范围中

**shared pages 共享页面**

几个不同的用户同时运行同一个程序时避免了在内存中有一个页面的两份副本。只读的页面（shared code）可以共享（且在不同进程中的逻辑地址要相同），但是数据页面（private code and data）则不能共享。

##### Hierarchical Page Tables 分层页表 & Hash PT & Inverted Page Tables（IPT）倒置页表

[分层页表 & 哈希页表 & 倒置页表](http://c.biancheng.net/view/1269.html)

##### Segmentation 分段

### 虚拟内存 Virtual Memory

#### 请求分页 Demand Paging

##### 缺页（page fault）

在请求分页系统中，每当所要访问的页面不在内存时，便产生一个缺页中断，请求操作系统将所缺的页调入内存。缺页中断作为中断同样要经历诸如：保护CPU环境、分析中断原因、转入缺页中断处理程序进行处理、恢复CPU环境等几个步骤。但与一般的中断相比，它有以下两个明显的区别：

- 在指令执行期间产生和处理中断信号，而非一条指令执行完后。

- 一条指令在执行期间，可能产生多次缺页中断。

##### 请求分页有效访问时间

缺页率 $0 \leq p \leq 1.0$

EAT = (1 – p) x memory access

\+ p (page fault overhead + swap page out

\+ swap page in

\+ restart overhead )

overhead：性能开销

##### 写入时复制 copy-on-write（cow）

如果有多个调用者（Callers）同时访问相同的资源（如内存或者是磁盘上的数据存储），他们会共同获取相同的指针指向相同的资源，直到某个调用者修改资源内容时，系统才会真正复制一份专用副本（private copy）给该调用者，而其他调用者所见到的最初的资源仍然保持不变。

由此父子进程可以共享内存中同一个页直到有进程需要修改这个页。

#### 页面置换 page replacement

无free frame时则进行页面置换

[置换算法](https://houbb.github.io/2020/10/04/os-10-page-exchange)

##### 1. 先进先出算法 FIFO

优先淘汰最早进入内存的页面，亦即在内存中驻留时间最久的页面（与进程实际运行时的规律不适应，因为在进程中，有的页面经常被访问）。

存在Belady's Anomaly：随着帧数的增加页面错误的数量会增加（LRU和OPT则是增加帧数，页面错误的数量将会减少）

##### 2. 最佳置换算法 OPT （optimal algorithm）

选择的被淘汰页面将是以后永不使用的，或者是在最长时间内不再被访问的页面,这样可以保证获得最低的缺页率。但实现并不实际，只能作为评价其他算法的标准。

##### 3. 最近最久未使用置换算法 LRU （Least Recently Used Alg）

选择最近最长时间未访问过的页面予以淘汰，它认为过去一段时间内未访问过的页面，在最近的将来可能也不会被访问。

为每个页面设置一个访问字段，来记录页面自上次被访问以来所经历的时间，淘汰页面时选择现有页面中值最大的予以淘汰（Every page entry has a counter; every time page is referenced through this entry, copy the clock into the counter）

需要寄存器和栈的硬件支持。LRU是堆栈类的算法。理论上可以证明，堆栈类算法不可能出现Belady异常。FIFO算法基于队列实现，不是堆栈类算法。

开销较大，两种实现方法：

- 系统维护一个页面链表，最近刚使用的页面作为首结点，最久未使用的页面作为尾结点，每次访问内存时，找到相应的页面，把它从链表中摘下来，再移动到链表之首，每次缺页中断发生时，淘汰链表末尾的页面。

- 设置一个活动页面堆栈：当访问某页时，将此页号入栈顶，并去除栈内的重复页。当需要淘汰一个页面时，总是选择栈底的页面，它就是最久未使用的。

##### 4. 时钟页面置换法（clock）

需要用到页表项的访问位（access bit），当一个页面被装入内存时，把该位初始化为0，然后如果这个页被访问（读/写）时，硬件把它置为1. 

把各个页面组织成环形链表（类似钟表面），把指针指向最老的页面（最先进来）；

当发生一个缺页中断，考察指针所指向的最老的页面，若它的访问为为0，则立即淘汰。若访问为1，则把该位置为0，然后指针往下移动一格。如此下去，直到找到被淘汰的页面，然后把指针移动到它的下一格。

##### 5. 二次机会法 Second-Chance

修改Clock算法，使它允许脏页总是在一次时钟头扫描中保留下来，同时使用脏位（dity bit,也叫写位）和使用位来指导置换

##### 6. 最不常用法 LFU

当一个缺页中断发生时，选择访问次数最少的那个页面，并淘汰之

#### 页面分配策略（allocation of frames）

驻留集：指请求分页存储管理中给进程分配的物理内存块的集合。在采用了虚拟存储技术的系统中，驻留集大小一般小于进程的总大小。

全局（global）置换：process selects a replacement frame from the set of all frames; one process can take a frame from another

局部（local）置换：each process selects from only its own set of allocated frames;

##### 1. 固定分配 fixed allocation

$s_{i} = $ size of process $p_i$

$S = \sum s_i$

m = total number of frames

$a_i = $ allocation for $p_i = \frac{s_i}{S} \times m$  

驻留集大小不变

 ##### 2. priority allocation

#### 颠簸 Thrashing （页面抖动）

在进程的页面置换过程中，频繁的页面调度行为成为抖动，或颠簸。如果一个进程在换页上用的时间多于执行时间，那么这个进程就在颠簸。

#### 工作集 Working-Set

工作集（或驻留集）是指在某段时间间隔内，进程要访问的页面集合。

经常被使用的页面需要在工作集中，而长期不被使用的页面要从工作集中被丢弃。为了防止系统出现抖动现象，需要选择合适的工作集大小。

Δ ≡ working-set window ≡ a fixed number of page references

Δ太小将无法包括一个完整的局部（locality），太大则会包括过多的局部。

$WSS_i$为进程$P_i$的工作集大小

$D = \sum WSS_i > m$时，颠簸将会发生

#### 伙伴系统 Buddy System

#### Slab allocation

#### TLB Reach

- The amount of memory accessible from the TLB

TLB Reach = (TLB Size) X (Page Size)

### 文件系统 File-System

文件：Contiguous logical address space

在用户进行的输入、输出中，以文件为基本单位。

#### 文件打开

首次使用文件时调用open()，os维护一个包含所有打开文件信息的表（打开文件表，open-file table）。当需要一个文件操作时，可通过该表的一个索引指定文件，就省略了搜索环节。当文件不再使用时，进程可以关闭它，操作系统从打开文件表中删除这一个条目。

- Open() system call returns a pointer to an entry in the open-file table

- File Control Block, FCB, ( per file ) containing details about ownership, size, permissions, dates, etc.

- Per-process table

  -   Current file pointer
  -   Access rights ...

-   System-wide table

  整个系统表包含进程相关信息，如文件在磁盘的位置、访问日期和大小。一个进程打开一个文件，系统打开文件表就会为打开的文件增加一个条目，并指向整个系统表的相应条目。

  -   Open count ，即文件打开计数器，记录多少进程打开了该文件。每个关闭操作close则使count递减，当打开计数器为0时，便是该文件不再被使用。系统将收回分配给该文件的内存空间等资源。

每个打开文件都有如下关联信息：

- 文件指针（file pointer）：系统跟踪上次读写位置作为当前文件位置指针。这种指针对打开文件的某个进程来说是唯一的，因此必须与磁盘文件属性分开保存。
- 文件打开计数（file-open count）：文件关闭时，操作系统必须重用其打开文件表条目，否则表内空间会不够用。因为多个进程可能打开同一个文件，所以系统在删除打开文件条目之前，必须等待最后一个进程关闭文件。该计数器跟踪打开或关闭的数量，当计数为0时，系统关闭文件，删除该条目。
- 访问权限（access rights）：每个进程打开文件都需要有一个访问模式（创建、只读、读写、添加等）。该信息保存在进程的打开文件表中一边操作系统能允许或拒绝之后的IO请求。

#### 文件逻辑结构

**无结构文件**：对于源程序、可执行文件、库函数等通常采用的是无结构文件形式，即流式文件，其长度以字节为单位。

**有结构文件**：按照记录的组成形式可以分成顺序文件、索引文件、索引顺序文件、散列文件（直接文件）。

- 顺序文件分为串结构（按存入时间的先后排列）和顺序结构（按关键字顺序排列）。顺序文件利于对记录进行批量操作时，即每次要读或写一大批记录；也只有顺序文件才能存储在磁带上。但查找、修改、增加或删除单个记录的操作比较困难
- 索引文件：可变长记录的文件。建立一张索引表以加快检索速度，索引表本身是顺序文件。
- 索引顺序文件（索引顺序表）：为顺序文件建立一张索引表，在索引表中为每组中的第一个记录建立一个索引项，其中含有该记录的关键字值和指向该记录的指针。

#### 目录结构

**单级目录结构**：整个文件系统只建立一张目录表，每个文件占一个目录项。访问一个文件时，先按文件名在该目录中查找到相应的FCB，经合法性检查后执行相应的操作。实现了按名存取，但是存在查找速度慢、文件不允许重名、不便于文件共享等缺点

**二级目录结构**：将文件目录分成主文件目录MFD（master file directory）和用户文件目录UFD（user file directory）两级。MDF记录用户名及相应用户文件所在的存储位置；UFD记录该用户文件的FCB信息。两级目录结构可以解决多用户之间的文件重名问题，文件系统可以在目录上实现访问限制。

**多级目录结构（树形目录结构 Tree-Structured Directories）**：用户要访问某个文件时用文件的路径名标识文件，文件路径名是一个字符串。从根目录出发的路径称为绝对（absolute）路径；从当前目录出发到所找文件为相对（relative）路径。通路上所有目录名与数据文件名用`/`连接。树形目录结构可便于实现文件分类，但不便于实现文件共享，在属性目录中查找一个文件，需要按路径名主机访问中间节点，增加了磁盘访问次数。

**无环图目录结构（acyclic-graph dir）**：在树形目录结构的基础上增加了一些指向同一节点的有向边，使整个目录成为一个有向无环图，实现文件共享。同时为每个共享节点设置一个共享计数器，每当途中增加对该节点的共享链时，计数器加1；每当某用户提出删除该节点时，计数器减1。仅当共享计数器为0时，才真正删除该节点，否则仅删除请求删除的用户的共享链。

用户B共享用户A的一个文件F时，系统创建一个link类型的新文件，也取名为F，并将文件F写入B的目录中，以实现用户B的目录与文件F的连接。在新文件中只包含被链接文件F的路径名。（即符号链接）

#### Linux磁盘分区

|           装置            |              linux内的文件名               |
| :-----------------------: | :----------------------------------------: |
|         IDE硬盘机         |                /dev/hd[a-d]                |
|    SCSI/SATA/USB硬盘机    |                /dev/sd[a-p]                |
|         USB快闪碟         |         /dev/sd[a-p]（与sata不同）         |
| 软盘驱动器（Floppy Disk） |                /dev/fd[0-1]                |
|          打印机           | 25针: /dev/lp[0-2]  USB: /dev/usb/lp[0-15] |
|           鼠标            | PS2: /dev/psaux  USB: /dev/usb/mouse[0-15] |
|     当前CDROM/DVDROM      |                 /dev/cdrom                 |
|        当前的鼠标         |                 /dev/mouse                 |

#### 文件系统挂载 Mounting

挂载（mounting）是指由操作系统使一个存储设备（诸如硬盘、CD-ROM或共享资源）上的计算机文件和目录可供用户通过计算机的文件系统访问的一个过程。

每个设备（文件系统）会设置一个挂载点（mount point），挂载点是一个空目录。一般来说必须有一个设备挂载在/这个根路径下面，叫做rootfs。其他挂载点可以是/tmp，/boot，/dev等等。

`$ mount /dev/dsk /users` 将 /dev/dsk 挂在 /users 下。

#### 文件共享 File Sharing

见 无环图目录结构（acyclic-graph dir）

Network File System (NFS) is a common distributed file-sharing method

#### 文件保护 File Protection

文件系统必须控制用户对文件的存取，即解决对文件的读（r）、写（w）、执行（x）的许可问题。

解决访问控制最常用的方法是根据用户身份进行控制。而实现基于身份访问的最为普通的方法是为每个文件和目录增加一个访问控制列表（Access-Control List，ACL），以规定每个用户名及其所允许访问的类型。

```c
|  - or d |    r|w|x    |    r|w|x    |    r|w|x    |
|file type|    Owner    |    Group    | Other Users |
```

Owner：创建文件的用户。

G：一组需要共享文件且具有类似访问的用户。

3）其他：系统内的所有其他用户。

[文件系统实现](http://blog.forec.cn/2017/01/05/os-concepts-11/)

#### 文件系统结构

内存和磁盘之间的 I/O 转移以块为单位而非字节。文件系统包括多层，自底向上为：

- I/O控制（I/O control）：由 设备驱动程序（device drivers） 组成
- 基本文件系统（basic file system）：只需要向设备驱动程序发送一般指令就可以对磁盘上的物理块做读写
- 文件组织模块（file- organization module）：将逻辑块地址转换成基本文件系统用的物理块地址。它也包括 空闲空间管理器（free space mgmt） 用来追踪未分配的块
- 逻辑文件系统（logical file system）：管理元数据（metadata），元数据包括文件系统的全部结构数据而不包括文件的具体内容。逻辑文件系统为文件组织模块提供所需的信息，通过 **文件控制块（file-control block，FCB）** 来维护文件结构，同时也负责保护和安全。

#### 虚拟文件系统 VFS （virtual file sys）

为用户程序提供文件和文件系统操作的统一接口，屏蔽不同文件系统的差异和操作细节。借助VFS可以直接使用`open()`、`read()`、`write()`这样的系统调用操作文件，而无须考虑具体的文件系统和实际的存储介质。

#### 目录实现

1. linear list：使用存储文件名和数据块指针的线性表。创建新文件时，必须首先搜索目录表以确定没有同名的文件存在，然后在目录表后增加一个目录项。删除文件则根据给定的文件名搜索目录表，接着释放分配给他的空间。费时。
2. hash table：根据文件名得到一个值，并返回一个指向线性列表中元素的指针。这种方法的有点事查找非常迅速，插入和删除也较简单，不过需要一些预备措施来避免冲突。定长问题可用chained-overflow hashtable

#### 块分配方法（文件实现）

[参考](http://c.biancheng.net/view/1302.html)

##### 1. 连续分配（contiguous allocation）

连续分配方法要求每个文件在磁盘上占有一组连续的块。可以用第一块的磁盘地址和连续块的数量来定义，这种排序使作业访问磁盘时需要的寻道数和寻道时间最小。

连续分配支持**顺序访问**和**直接访问**。其优点是实现简单、存取速度快。缺点在于，文件长度不宜动态增加。此外，反复增删文件后会产生外部碎片，并且很难确定一个文件需要的空间大小，因而只适用于**长度固定的文件**。

**可扩展文件系统（Extent-based file systems）**

An **extent** is a contiguous block of disks

-   Extents are allocated for file allocation
-   A file consists of one or more extents.

##### 2. 链接分配（linked allocation）

链接分配解决了连续分配的碎片和文件大小问题，不会产生外部碎片。

采用链接分配，每个文件对应一个磁盘块的链表；磁盘块分布在磁盘的任何地方，除最后一个盘块外，每个盘块都有指向下一个盘块的指针。目录包括文件第一块和最后一块的指针。

创建新文件时，目录中增加一个新条目。链接分配中每个目录项都有一个指向文件首块的指针，初始化为null，字段大小设置为0。写文件会通过空闲空间管理系统找到空闲块，将该块链接到文件的尾部，以便于写入。（文件分配表 FAT File-Allocation Table的使用）

**无法直接访问盘块**，只能通过指针顺序访问文件（从首块开始），以及盘块指针消耗了一定的存储空间。此外可靠性也存在问题，操作系统软件错误或磁盘硬件故障可能导致获得一个错误指针。

##### 3. 索引分配（indexed allocation）

在没有 FAT 时，链接分配不能支持髙效的直接访问，因为块指针与块一起分散在整个磁盘上，并且必须按序读取。索引分配通过将所有指针放在一起，即**索引块**，解决了这个问题。

每个文件都有自己的索引块，这是一个磁盘块地址的数组。索引块的第 i 个条目指向文件的第 i 个块。目录包含索引块的地址（图 4）。当查找和读取第 i 个块时，采用第 i 个索引块条目的指针。

索引分配支持**直接访问**，并且没有外部碎片问题。但会浪费空间，

**多级索引**：链接表示的一种变种是，通过第一级索引块指向一组第二级的索引块，它又指向文件块。当访问一块时，操作系统通过第一级索引查找第二级索引块，再采 用这个块查找所需的数据块。这种做法可以持续到第三级或第四级，具体取决于最大文件大小。

混合索引：将多种索引分配方式相结合的分配方式。例如，系统即采用直接地址，又采用单级索引分配方式或两级索引分配方式。

#### 空闲空间管理

##### 1. bit vector

将空闲空间用 **位图（bit map）** 或 **位向量（bit vector）** 表示

bit[i] = 1 ⇒ block[i]空闲

bit[i] = 0 ⇒ block[i]占用

##### 2. link list & group

将所有空闲磁盘块用链表链接，将指向第一个空闲块的指针放在磁盘的一个特殊位置，同时也缓存到内存里。第一块空闲块中包含了指向下一个空闲磁盘块的指针。

组是对空闲链表的改进：将 n 个空闲块的地址存在第一个空闲块里，前 n-1 个地址都指向真正的空闲块， **最后一个地址指向了另一个包含另外 n 个空闲块的块地址** 。

##### 3. counting

通常会有多个连续的块需要同时分配、释放。因此可以不记录 n 个空闲块地址，而是记录连续多块空闲块的第一块的地址，以及连续的空闲块的数量。

#### 效率efficiency & 性能performance

efficiency depends on: disk allocation and directory algorithms

performance

##### 页缓存 page cache

[参考](https://zhuanlan.zhihu.com/p/35448479)

简而言之是将文件数据作为页而不是磁盘块缓存到虚拟内存。

#### 恢复 Recovery

一致性检查（consistency checking）：将目录结构数据与磁盘数据比较并纠错

备份（back up）：把磁盘数据备份到另一个设备

日志（Log Structured）：文件系统记录更新 为事务（transaction），commit后事务写进日志。

### 大容量存储系统 Mass-Storage System（磁盘组织管理）

[参考](https://cloud.tencent.com/developer/article/1747166)

#### 磁盘结构

定位时间（positioning time），即随机访问时间（random access time），由寻道时间（seek time）（移动磁臂到所要的柱面所需时间）和旋转延迟（rotational latency）（等待所要的扇区旋转到磁臂下所需时间）组成。

#### 磁盘调度

可以参考PPT chapter12 的磁道展开图

##### 1. FCFS调度

##### 2. SSTF调度（shortest-seek-time-first 最短寻道时间优先）

在将磁头移到远处以处理其他请求之前，先处理靠近当前磁头位置的请求

磁头移动距离最小，但可能会导致饥饿

##### 3. SCAN调度（elevator algorithm）

磁臂从磁盘的一端向另一端移动，同时当磁头移过每个柱面时，处理位于该柱面上的服务请求。当到达另一端时，磁头改变移动方向，处理继续。磁头在磁盘上来回扫描。

##### 4. C-SCAN调度（circular SCAN）

提供一个更为均匀的等待时间。

与SCAN一样，C-SCAN将磁头从磁盘一端移到磁盘的另一端，随着移动不断地处理请求。不过，当磁头移到另一端时，它会马上返回到磁盘开始，返回时并不处理请求。

##### 5. C-LOOK调度

SCAN和C-SCAN使磁头在整个磁盘宽度内进行移动

若磁头只移动到一个方向上最远的请求为止，接着马上回头，而不是继续到磁盘的尽头。这种形式的SCAN和C-SCAN称为LOOK和C-LOOK调度。

**SSTF优于FCFS  SCAN和C-SCAN对于磁盘负荷较大的系统会执行的更好，这是因为它不可能产生饿死问题。**

#### 磁盘管理

disk sector

```c
|           header           | data |         trailer       |
|synchronization information |      | error-correcting code | 
```

#### 引导块

开机步骤：

- 首先加电引导，然后运行系统ROM上的代码，开始启动。然后从MBR（master boot record 主引导记录）中读取引导代码。MBR中包含一个硬盘分区列表和一个说明系统引导分区的标志。
- 系统确定引导分区，读取该分区第一个扇区（即引导扇区（boot sector））并继续余下的启动过程，包括加载各种子系统和系统服务。

#### RAID 多磁盘管理

[参考](https://zh.wikipedia.org/wiki/RAID)

RAID（Redundant Array of Inexpensive Disks）称为廉价磁盘冗余阵列。RAID 的基本原理是把多个便宜的小磁盘组合到一起，成为一个磁盘组，使性能达到或超过一个容量巨大、价格昂贵的磁盘。

##### RAID级别

1. RAID0

   RAID0以条带的形式将数据均匀的分布在阵列上的各个磁盘之上。是一种简单的、无数据校验的数据条带化技术。

   优点：低成本、高读写性能、 100% 的高存储空间利用率 不存在校验、不会占用太多的CPU;设计、使用和配置比较简单

   缺点：无冗余，一旦数据损坏，将无法恢复

2. RAID1

   RAID1 称为镜像，它将数据完全一致地分别写到工作磁盘和镜像磁盘。RAID1 提供了最佳的数据保护，一旦工作磁盘发生故障，系统自动从镜像磁盘读取数据，不会影响用户工作。

   优点：具有100%的数据冗余，提供最高的数据安全保障，理论上可以实现2倍的读取效率，设计和使用也比较简单；允许损坏1块磁盘。

   缺点：开销大，磁盘空间的利用率只有50%，在写操作方面性能并没有提升

3. RAID2

   这是RAID 0的改良版，以[汉明码](https://zh.wikipedia.org/wiki/汉明码)（Hamming Code）的方式将数据进行编码后分割为独立的比特，并将数据分别写入硬盘中。因为在数据中加入错误修正码（ECC，Error Correction Code），所以数据整体的容量会比原始数据大一些。

   RAID 2最少要三台磁盘驱动器方能运作。

4. RAID3～RAID6见wiki

5. RAID10/01

   RAID 10是先分割资料再镜像，再将所有硬盘分为两组，视为以RAID 1作为最低组合，然后将每组RAID 1视为一个“硬盘”组合为RAID 0运作。

   RAID 01则是先镜像再将资料到分割两组硬盘。它将所有的硬盘分为两组，每组各自构成为RAID 0作为最低组合，而将两组硬盘组合为RAID 1运作。

### I/O系统

[参考](https://houbb.github.io/2020/10/04/os-14-io)

#### I/O控制方式

##### 1. 程序直接控制方式

即轮询（polling），CPU的高速性和I/O设备的低速性致使CPU的绝大部分时间都处于等待I/O设备完成数据I/O的循环测试中（busy-wait）

##### 2. 中断驱动方式

从I/O控制器的角度来看，I/O控制器从CPU接收一个读命令，然后从外围设备读数据。一旦数据读入到该I/O控制器的数据寄存器，便通过控制线给CPU发出一个中断信号，表示数据已准备好，然后等待CPU请求该数据。I/O控制器收到CPU发出的取数据请求后，将数据放到数据总线上，传到CPU的寄存器中。至此，本次I/O操作完成，I/O控制器又可幵始下一次I/O操作。

数据中的每个字在存储器与I/O控制器之间的传输都必须经过CPU导致了中断驱动方式仍然会消耗较多的CPU时间。

##### 3. DMA方式

Direct Memory Access （直接存储器存取）方式的基本思想是在I/O设备和内存之间开辟直接的数据交换通路，彻底解放CPU。

- 基本单位是数据块。
- 所传送的数据，是从设备直接送入内存的，或者相反。
- 仅在传送一个或多个数据块的开始和结束时，才需CPU干预，整块数据的传送是在 **DMA控制器**（DMA controller）的控制下完成的。

##### 4. 通道控制方式

I/O通道是指专门负责输入/输出的处理机。I/O通道方式是DMA方式的发展，它可以进一步减少CPU的干预，即把对一个数据块的读（或写）为单位的干预，减少为对一组数据块的读（或写）及有关的控制和管理为单位的干预。

#### I/O核心子系统

##### I/O层次结构

1）用户层IO软件：实现与用户交互的接口，用户可直接调用在用户层提供的、与IO操作有关的库函数，对设备进行操作。

2）设备独立性软件：用于实现用户程序与设备驱动器的统一接口、设备命令、设备保护，以及设备分配与释放等，同时为设备管理和数据传送提供必要的存储空间。

3）设备驱动程序：与硬件直接相关，用于具体实现系统对设备发出的操作指令，驱动IO设备工作的驱动程序。

4）中断处理程序：用于保存被中断进程的CPU环境，转入相应的中断处理程序进行处理，处理完并回复被中断进程的现场后，返回到被中断进程。

##### I/O调度（scheduling）

调度一组IO请求即确定一个好的顺序来执行这些请求。

##### Buffering

store data in memory while transferring between devices

- ●  To cope with device speed mismatch, e.g. receiving data from

  modem to disk.

- ●  To cope with device transfer size mismatch, e.g. network packet

##### 高速缓存caching

##### SPOOLing假脱机技术

外部设备联机并行操作（SPOOL,Simultaneous Peripheral Operations On-line）

为了缓和CPU的高速型与IO设备低速性之间的矛盾而引入了脱机输入、脱机输出技术。该技术是利用专门的外围控制机，将低速IO设备上的数据传送到高速磁盘上；或者相反。

