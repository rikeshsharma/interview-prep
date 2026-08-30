# Synchronization

- Multiple processes can concurrently access the
same shared memory location
- This may lead to data race and hence final undesired output
- The remedy is that the OS must synchronize such
concurrent accesses enforcing a deterministic order
between these operations

- **Point to Point Synchronization**: Point-to-point synchronization 
means synchronizing two specific execution entities—usually two threads 
or two processes—so that one waits for the other at a particular point. 
  - Example: Suppose Thread A produces some data and Thread B consumes it
             Thread B should not consume the data before A produces it.

- **Barrier Synchronization**: It is a type of synchronization in which
multiple threads or processes must all reach certain point before any
of them can continue.
  - Example: Imagine a program doing a computation in phases:       Thread 1: Work ──────> WAIT
             Each thread processes part of Phase 1. But Phase 2     Thread 2: Work ──────> WAIT
             cannot start until every thread has finished Phase 1.  Thread 3: Work ──────> WAIT
                                                                    Thread 4: Work ──────> WAIT
                                                                          |
                                                                     All arrived
                                                                          |
                                                                          v
                                                                    Thread 1: Continue
                                                                    Thread 2: Continue
                                                                    Thread 3: Continue
                                                                    Thread 4: Continue

### Critical Section

- A critical section is a part of a program where a thread/process accesses 
shared data or a shared resource, and therefore must be protected from concurrent access.
- The goal is that only one thread/process access this section at a time so when 
simultaneous access may lead to data race / race condition.
- The critical section must be executed in time mutually exclusive manner.
  - also known as the **atomic region**

- 3 Parts : entry to, body of and exit from critical section

- Data Race: Two or more thread or processes involved
             accesses the same memory location
             atleast on of them write
             no proper synchronization between them
- Race condition: A race condition is a broader concept where the program's 
                  correctness depends on the timing/order of concurrent operations.

### Mutual Exclusion Algorithm

- It define the entry and exit protocol of critical section
  - software solution
  - hardware to guarantee atomicity

- 3 criteria
  - mutual exclusion: atmost one process/thread can be inside a critical section at a point in time
  - progress: if no one is inside critical section, atleast one should be selected to enter and this
              selection cannot be indefinitely postponed.
  - bounded: number of time other process has be allowed to enter a critical section from the time
            a given process has expressed it interest to enter must be bounded.
- they are also called **lock algorithm**

### Dekker's Algorithm
defined
i in domain {0, 1} and j = 1-i
Process 0 -> i = 0 
Process 1 -> i = 1 
turn = 0

Dekker's algorithm uses:
1. Two boolean flags - shared
   - flag[0] → Process 0 wants to enter the critical section.
   - flag[1] → Process 1 wants to enter the critical section.
2. One shared variable
   - turn
   - Indicates whose turn it is when both processes want to enter simultaneously.

```cpp
flag[i] = true; // I want enter
while(flag[j]) { // --- check whether the other wants to enter too, if yes allow it first
  if(turn == j) { // check whether its their turn if it their turn then
    flag[i] = false;  // I dont want to enter and will
    while(turn == j); // wait until its not their turn
    flag[i] = true; // I want to enter again but first I will check ---
  }
}

// critical section

turn = j; // My turn is over, its others turn
flag[i] = false; // I want to exit, so do not want to enter.
```

### Peterson’s algorithm
defined
i in domain {0, 1} and j = 1-i
Process 0 -> i = 0 
Process 1 -> i = 1 
turn = 0

Peterson's algorithm uses:
1. Two boolean flags - shared
   - flag[0] → Process 0 wants to enter the critical section.
   - flag[1] → Process 1 wants to enter the critical section.
2. One shared variable
   - turn
   - Indicates whose turn it is when both processes want to enter simultaneously.

```cpp
flag[i] = true;
turn = j;

while (flag[j] && turn == j);   // wait

// Critical Section

flag[i] = false;
```

- "I want to enter, but I'll give the other process priority. 
If they also want to enter and it's their turn, I'll wait."


### Lamport's Bakery Algorithm

- Imagine you enter a bakery.
- You don't immediately go to the counter.
- You first take a token:
  - You → Token #17
- Then you wait.
- If someone has:
  - Token #15
- they go before you.
- If someone has:
  - Token #18
- you go before them.
- So the rule is simply:
- Smallest ticket goes first.

Lamport's Bakery Algorithm does exactly this with processes.

```cpp
choosing[i] = true;
number[i] = 1 + max(number[0], number[1], ..., number[N-1]);
choosing[i] = false;
for (int j = 0; j < N; ++j) {
    if (j == i)
        continue;

    while (choosing[j]);

    while (number[j] != 0 &&
           (number[j], j) < (number[i], i));
}

// Critical Section

number[i] = 0;
```

### Hardware support

1. TestAndSet: atomic operation provided by hardware
- this is used to implement spinlock
  - wastage of cpu cycles
- ts r addr

conceptually 
```cpp
// this function is provided by hardware
bool test_and_set(bool& lock) {
    bool old = lock;
    lock = true;
    return old;
}

bool lock = false;
while (test_and_set(lock)) {
    // wait
}
// Critical Section
lock = false;
```

in modern cpp
```cpp
std::atomic<bool> lock{false};
while (lock.exchange(true)) {
    // spin
}
// Critical Section
lock.store(false);
```

2. Compare and Swap: atomic operation in which the value of addr1 is compared with
some value v, if they are same then swaps value of addr1 and addr2.

cmpxchg v addr1 addr2

```cpp
bool CAS(bool v, bool* a, bool* b) {
  if(*a == v) {
    *a = *b;
    *b = v;
    return true;
  }
  return false;
}

bool lock = false;
bool x = true; // not shared
while (!CAS(false, &lock, &x)) {
    // spin
}
// Critical Section

lock = false;
```

3. Exchange: atomic operation in which value of two address is exchanged

xchg addr1 addr2

```cpp
bool xchg(bool *a, bool *b) {
  bool temp = *a;
  *a = *b;
  *b = temp;
  return temp;
}

bool lock = false;
bool x = true; // not shared
while(xchg(&lock, &x));

// critical section

lock = false;
```

### Spinlock
- All the algorithms Dekker's, Pattinson, Lambart Bakery, TestAndSet, CAS, Exchange
spins until the acquire lock, they are called spinlock algorithm
- busy waiting
- wasting cpu cycles
- alternative to cpu cycle is do context switch but this has high overhead.

### Two Phase Locking

- Ideal solution is to spin for a while hoping to get the lock then do context switch
  - Referred to as **Two Phase Locking**

1. Do not spin just yield: call yield() to do context switch

- This is achieved by **mutex** in modern c++

2. Futex (Fast Userspace Mutex) : A futex (fast userspace mutex) is a Linux kernel mechanism 
that lets threads efficiently wait and wake on a shared memory value. Synchronization can stay 
entirely in userspace on the uncontended fast path, while the kernel is used to block and wake 
threads when there is contention.

          Try CAS
             │
       ┌─────┴─────┐
       │           │         That fast userspace path + kernel sleep/wakeup slow path is the core idea.
    SUCCESS       FAIL
       │           │
       ▼           ▼
    Enter       Futex wait
                  │
                  ▼
                SLEEP
                  │
             futex wake
                  │
                  ▼
               Try CAS

### Conditional Variable

- Suppose we have a producer and a consumer.
There is a shared queue:
             Shared Queue
        ┌────────────────────┐
Producer│                    │Consumer
  ─────►│       [ ... ]      │─────►
        └────────────────────┘
The consumer wants to do:
"Give me an item from the queue."

But what if the queue is empty?
queue = []
The consumer cannot consume anything.
So it needs to wait until:
queue is not empty
This is the fundamental problem that leads us to **condition variables**

- naive solution would be: spin while the value is not available.
  - This is busy waiting / spinning

- **Conditional Variable** : A condition variable is a mechanism that allows a thread 
to sleep while waiting for some shared state/condition to become true, and allows another 
thread to wake it when that state may have changed.
```cpp
- consumer
lock(mutex);
while (queue.empty()) {
    wait(cv, mutex); // release lock + sleep + reacquire lock behavior is the heart of condition variables.
}
item = queue.pop();
unlock(mutex);

- producer
lock(mutex);
queue.push(item);
signal(cv);
unlock(mutex);
```
- Summary
  1. Mutex protects shared state.
  2. A condition variable lets a thread sleep while waiting for shared state to become suitable for progress.
  3. wait() conceptually does:
      release mutex → sleep → wake → reacquire mutex
  4. Always think:
      while (!condition)
        wait();

- In modern c++
#include <condition_variable> <- header file
std::conditional_variable

- used together with 
std::mutex
std::unique_lock

-  The most important pattern is
```cpp
std::unique_lock<std::mutex> lock(mutex);

while (!condition) {
    cv.wait(lock);
}
```

Example
```cpp
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;

// producer
void producer() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(42);
    }
    cv.notify_one();
}

// consumer
void consumer() {
    std::unique_lock<std::mutex> lock(mtx); // beacuse the cv
                                            // require it to temporarily
                                            // unlock
    while (queue.empty()) {
      // cv.wait(lock); 
      // is conceptually:
      // 1. Unlock mutex
      // 2. Put current thread to sleep
      // 3. Someone calls notify
      // 4. Wake thread
      // 5. Reacquire mutex
      // 6. Return from wait()
        cv.wait(lock);
    }

    int value = queue.front();
    queue.pop();
}
```

### Why while not if ?
- Because
- cv.notify_one();
- does not mean:
- "The condition is definitely true."
- It means:
- "Something changed; you should wake up and check."

- modern c++ gives us even nicer version
```cpp
cv.wait(lock, [] {
    return !queue.empty();
});
```

### notify_one() vs notify_all()

- notifies one among many threads
- notifies all the threads

### Complete Producer Consumer Example

```cpp
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> queue;

void producer() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(42);
        std::cout << "Produced 42\n";
    }
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] {
        return !queue.empty();
    });
    int value = queue.front();
    queue.pop();
    std::cout << "Consumed " << value << '\n';
}

int main() {
    std::thread c(consumer);
    std::thread p(producer);

    c.join();
    p.join();
}
```