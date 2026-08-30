# Operating System

- It is a piece of system software that
  1. schedules and 
  2. virtualizes 
    computing resource like
    memory, hardrive, processor and I/O

### Goals of OS

1. Efficient virtualization of physical resource
2. Efficient support for correct handling of concurrent execution
3. Efficient file system for persistent storage
4. Protection, Isolation and Security
5. Reliability and failure freedom

### Functionality of OS

1. To improve performance
  - Job Scheduling, Context Switching and Memory management
2. To improve ease of use
  - File system, I/Os and Security

### 2 Mode of Operation

1. User mode: isolated virtual address space for each process
isolated execution for each process and no direct access to hardware

2. Kernel mode: has unrestricted access to hardware
    including the execution of previliged instruction

### 4 Basic OS Modules

1. Process Management
  - creation, deletion and scheduling processes
  - support for communication between processes
  - synchronizing communicating processes
  - handling deadlocks
2. Memory Management
  -  allocation and deallocation of memory
3. Storage Management
  - implementing a virtual environment call file system
4. Protection