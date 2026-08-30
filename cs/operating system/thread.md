# Thread

- A thread is an independent unit of execution inside a process

PROCESS
│
├── Code
├── Global variables
├── Heap
├── Open files
│
├── Thread 1
│    ├── Program Counter
│    ├── Registers
│    └── Stack
│
├── Thread 2
│    ├── Program Counter
│    ├── Registers
│    └── Stack
│
└── Thread 3
     ├── Program Counter
     ├── Registers
     └── Stack

- For a given process multiple threads provide multiple unit of 
execution.


### Process vs Thread

- A process generally has its own
  - text/code
  - virtual address space
  - heap
  - global and static data
  - open files/resource

- Threads within the same process share most of those resources
  - program counter
  - stack
  - stack pointer
  - processor registers
  - thread local storage

so

                    PROCESS
                       │
        ┌──────────────┼──────────────┐
        │              │              │
        v              v              v
     Thread 1       Thread 2       Thread 3
        │              │              │
      Stack          Stack          Stack
        │              │              │
       PC             PC             PC
       Registers      Registers      Registers

        └──────────── shared ────────────┘

          Code
          Global variables
          Heap
          Address space
          Resources

- This sharing is powerful, but it creates one of the biggest 
problems in concurrent programming : Race conditions.


### Thread Context

- Thread context
      │
      ├── Program Counter
      ├── CPU registers
      ├── Stack Pointer
      ├── CPU flags/status
      ├── Stack
      └── Thread-local 
      
### Process switch:
    CPU state
    +
    potentially address-space/memory-management state
    +
    other process-specific state

### Thread switch within same process:
    CPU execution state
    +
    thread-specific state

### Writing thread in c++

1. Simplest Example
```cpp
#include <iostream>
#include <thread> // standard library for thread in c++

void task() {
    std::cout << "Hello from thread!\n";
}

int main() {
    std::thread t(task); // creating a thread like object

    t.join(); // Wait (main thread) until thread t finishes

    std::cout << "Main thread finished\n";
}
```

2. Passing arguments to thread
```cpp
#include <iostream>
#include <thread>

void printNumber(int x) {
    std::cout << x << '\n';
}

int main() {
    std::thread t(printNumber, 42);

    t.join();
}
```

3. Multiple threads
```cpp
#include <iostream>
#include <thread>

void task(int id) {
    std::cout << "Thread " << id << '\n';
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();
}
```
The order of thread scheduling is not guarantee.

4. Lambda threads
```cpp
#include <iostream>
#include <thread>
#include <functional> // Required for std::ref

int main() {
    int count = 10;

    // Modifying the actual 'count' variable safely
    std::thread t([](int& c) {
        c += 5; 
    }, std::ref(count)); // std::ref forces passing by reference

    t.join();
    std::cout << "Updated Count: " << count << "\n"; // Output: 15
}
```

- std::jthread : with std::thread we need to manually join() the thread so that
                the main thread wait for the thread before proceeding
               : with std::jthread this is not needed manually

### Mental model

                       Your process
                            |
        ┌───────────────────┴─────────────────────┐
        |                   |                     |
   Main thread          Worker thread 1     Worker thread 2
        |                   |                     |
      main()               foo()                foo()

    
Process[Main Thread] --- spawns a thread ---> Process[Main Thread, Worker Thread]

- join() : Main thread waits for the worker thread to complete
         : t.join()
         : If it is not called
          - main thread reaches the end while t still represents a running thread.
           For a std::thread, destroying a joinable thread calls std::terminate().

- detach() : Let the Worker thread continue running independently.
           : The worker becomes an independent execution flow.
           : If the worker thread uses some variable that is owned by main
              then when main terminate that variable get deallocated while the 
              thread continue to be unaware of this leading to bugs. 