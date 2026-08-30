# Process

- A process is any executable in action.
- An executable is a passive entity, a process 
is an active instantiation of the executable.
- Process state:
  - Created
  - Ready
  - Running
  - Sleep
  - Terminated/Zombie

  Created ---> Ready ---> Running ---> Terminated/Zombie
                ^           |
                |           | 
                +-- Sleep --+

- Handling of multiple processes are necessary for
efficient and optimal and maximize resource utilization

### Each Process has

1. Text (code)
2. global user variable and data structures
3. Processor register values
  - Intermediate values are maintained in processor register
  - stack pointer: points to the top of stack
  - program counter: keeps track of which instruction is executing
4. Process table and u area
5. kernel mode stack and user mode stack
6. Stack and Heap
7. List of open files and their seek pointers: UFDT 

These together defines **Process Context**

- PCB Process Control Block: It is a kernel data structure
that maintains all the information related to process context,
including current process state.

### Process Context Switch

- It is the way in which the old process context is saved and 
the new process context is restored or loaded into the process context registers.

1. Ready-Queue: Queue of the Ready to run processes.
2. Wait-Queue: Queue of the waiting processes on some device or event.

The opertion in which
CPU executing A
       |
       | save A's CPU context
       v
A becomes Ready
       |
       | load B's CPU context
       v
CPU executes B

is Called a Process Context switch

CPU context <- context switch states
   |
   +-- Program Counter (PC)
   +-- Stack Pointer (SP)
   +-- General-purpose registers
   +-- CPU flags/status register
   +-- architecture-specific state

### 2 Types of Processes

1. CPU-bound: These are processes that mostly do compute
  major portion of their life is executing or in wait queue.

2. I/O-bound: These are processes that spend significant
  amount of time in I/O. major portion of life spent in sleep.