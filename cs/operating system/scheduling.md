# Scheduling
 
### Process Scheduling

- Scheduling Algorithms: The algorithm that selects one of the many
processes waiting in the ready-queue for execution on the processor next.
  - 2 types of schedulers
    - short-term schedulers : decides CPU allocation among runnable processes
    - medium-term schedulers : controls which processes remain in memory by 
                               temporarily suspending/swapping them.

- Multiprocessing: Executing independent or communicating processes simultaneously or
in a time shared manner

- Multithreading: Executing possibly dependent and/or communicating parts of the same
process simultaneously in different thread of control.

- Multiprogramming: Executing multiple programs in different process simultaneously.

### 4 Possible circumstances

- Scheduler can be invoked in four possible circumstances
  - non-preemptive/co-operative scheduling
    1. currently running process goes on a long latency system call 
    2. currently running process terminates
  - preemptive scheduling
    3. a new process is created or a process completes a long latency system call
    4. currently running process receives a timer interrupt

### Metrics

  1. Maximize Throughput: rate of processes completed
  2. Minimize turnaround time: time of completetion - time of arrival
  3. Minimize wait time: time in RUNNABLE state
  4. Minimize response time (fairness metric)

### FCFS First Come First Serve

- non-preemptive scheduling algorithm
- convoy effect: if one process has large CPU burst and other has smaller
- can have unbounded average wait time

### SJF Shortest Job First

- non-preemptive shortest next CPU burst
- provably optimal that acheives
  - minimum average wait time
  - minimum average turnaround time                          [Optimizes Average Turnaround Time]
                                                           [Unfair because penalises long cpu burst] ---> **Performance is inversely related to Fairness**
- Preemptive                                               
  - Shortest remaining time first
  - Shortest time to completion first

### Priority Based Scheduling

- Priority: assigned by kernel
            assigned by user
- Process with highest priority is scheduled first
  - can be preemptive or non-preemptive
- a steady flow of high priority processes can starve the low priority for cpu
  - age based priority modulation is required
- SJF is a special priority based scheduling

### Round Robin Scheduling

- Preemptive quantum scheduling
- The ready queue is treated as a circular FIFO and
each process in the FIFO order is assigned a fixed
time slice or quantum for execution
- If the running process goes to sleep or terminates         [Optimizes Average Response Time]
before the expiry of the quantum, the next process in        [Fair Give turn to all job equally] ---> **Performance is inversely related to Fairness**
the FIFO order is scheduled
- If the running process’s quantum expires, it is put
back at the tail of the ready queue

### Job of scheduler

- The scheduler views a process as a sequence of
interleaved CPU and I/O bursts
- Ideally, the scheduler’s goal is to overlap all I/O bursts
with available CPU bursts
- In general, a scheduling algorithm schedules CPU
bursts only, I/O bursts get taken care of on their own

### MLFQ Multi Level Feedback Queue

-  MLFQ is a family of scheduling algorithm that tries
to achieve these goals - minimize turnaround time and minimize
response time.
- multiple ready queue each having its own policy

- maintain multiple ready queue ordered by priority
- process within each queue are scheduled using RR
- A new process always enters highest priority queue,
but can move between queue during its life
- process in a given queue is scheduled using RR
provided all the queue with higher priority level than
it, is already empty
- If a running process uses up the complete scheduling 
quantum of RR, it is inferred to be a less interactive
process and demoted one level down in priority i.e., 
enqueued into the next lower priority queue
- If a running process invokes a blocking I/0 before 
completing the scheduling quantum of RR, its priority 
is not changed and kept in the same queue

### Deadlines

- Hard Deadlines
- Soft Deadlines
- Earliest deadline first EDF