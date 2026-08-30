# Semaphores

- Mutual exclusion or lock algorithm grants access to a number of
processes into a critical section one at a time.
- What if we want a bounded number of processes to access a resource
simultaneously? This is a form of synchronization.
- Consider a bounded buffer (a finite array); a
number of producer processes can write new values
into the array (provided the array is not full), which a
number of consumer processes can read (provided
the array is not empty)
- the solution of one process at a time is suboptimal here because
there is no reason to prevent multiple concurrent productions as long
as there is room in the buffer symmetrically, multiple concurrent
consumptions should be allowed
- A semaphore is a synchronization mechanism that controls how many 
threads can access shared resource at the same time.

### Mutex vs Semaphore

- A mutex is a locking tool that allows only one thread to access a resource 
at a time and requires the same thread to unlock it, while a semaphore is a 
signaling tool that uses an integer counter to manage access to one or more shared resources.

| **Feature** | **Mutex** | **Semaphore** |
|---|---|---|
| **Primary Role** | Mutual exclusion (locking) | Signaling and synchronization |
| **Ownership** | **Owned** by the thread that locks it | **Not owned** by a specific thread |
| **Value Range** | Binary (`0` or `1`) | Non-negative integer (`0` to `N`) |
| **Who Can Unlock / Signal** | Only the thread that locked it can unlock it | Any thread can signal (increment) it |
| **Main Use Case** | Protecting a critical section | Managing a pool of resources or signaling between threads |

### 2 types of Semaphores

1. Binary Semaphore: allow access to shared resource one at a time : can be used to implement locks
2. Counting Semaphore: allows access for k resource pool to a number of processes or thread

### Example of semaphores in c++

1. Bounded Buffer
3 producers
2 consumers
Array/buffer size = 5
Each producer produces 10 items
Total items = 30, so consumers together consume all 30.

```cpp
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>
#include <vector>

constexpr int BUFFER_SIZE = 5;
constexpr int NUM_PRODUCERS = 3;
constexpr int NUM_CONSUMERS = 2;
constexpr int ITEMS_PER_PRODUCER = 10;

// Fixed-size shared buffer
std::array<int, BUFFER_SIZE> buffer;

// Circular-buffer indices
int writeIndex = 0;
int readIndex = 0;

// Protects access to buffer, writeIndex and readIndex
std::mutex bufferMutex;

// Number of empty positions in the buffer.
// Initially all 5 positions are empty.
std::counting_semaphore<BUFFER_SIZE> emptySlots(BUFFER_SIZE);

// Number of filled positions in the buffer.
// Initially there are no items.
std::counting_semaphore<BUFFER_SIZE> fullSlots(0);

// Just to make console output readable.
std::mutex coutMutex;


// ---------------------------------------------------------
// PRODUCER
// ---------------------------------------------------------

void producer(int producerId) {
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        int item = producerId * 100 + i;

        // Wait until there is an empty slot.
        //
        // If the buffer is full:
        //
        //     full full full full full
        //
        // this thread blocks here.
        emptySlots.acquire();
        {
            // We have an empty slot.
            // Now protect the actual buffer operation.
            std::lock_guard<std::mutex> lock(bufferMutex);

            buffer[writeIndex] = item;

            {
                std::lock_guard<std::mutex> outputLock(coutMutex);
                std::cout << "Producer " << producerId
                          << " -> buffer[" << writeIndex
                          << "] = " << item << '\n';
            }

            // Move to the next position.
            // % BUFFER_SIZE makes the buffer circular.
            writeIndex = (writeIndex + 1) % BUFFER_SIZE;
        }

        // We added one item.
        //
        // Therefore the number of available filled slots
        // increases by one.
        fullSlots.release();

        // Just to make the execution easier to observe.
        std::this_thread::sleep_for(
            std::chrono::milliseconds(50));
    }
}


// ---------------------------------------------------------
// CONSUMER
// ---------------------------------------------------------
void consumer(int consumerId) {
    // Each consumer knows how many total items it must consume.
    //
    // Total items:
    //
    // 3 producers × 10 items = 30
    //
    // 30 / 2 consumers = 15 items each.
    constexpr int ITEMS_PER_CONSUMER =
        (NUM_PRODUCERS * ITEMS_PER_PRODUCER) / NUM_CONSUMERS;

    for (int i = 0; i < ITEMS_PER_CONSUMER; ++i) {
        // Wait until there is an item to consume.
        //
        // If the buffer is empty:
        //
        //     empty empty empty empty empty
        //
        // this thread blocks here.
        fullSlots.acquire();
        int item;
        {
            // We know at least one item exists.
            // Protect the actual buffer operation.
            std::lock_guard<std::mutex> lock(bufferMutex);

            item = buffer[readIndex];
            {
                std::lock_guard<std::mutex> outputLock(coutMutex);
                std::cout << "Consumer " << consumerId
                          << " <- buffer[" << readIndex
                          << "] = " << item << '\n';
            }
            // Move to the next position.
            readIndex = (readIndex + 1) % BUFFER_SIZE;
        }
        // We removed one item.
        //
        // Therefore one more empty slot is available.
        emptySlots.release();
        // Just to make the execution easier to observe.
        std::this_thread::sleep_for(
            std::chrono::milliseconds(80));
    }
}


// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------
int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Start consumers.
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.emplace_back(consumer, i);
    }

    // Start producers.
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(producer, i);
    }

    // Wait for all producers.
    for (auto& t : producers) {
        t.join();
    }

    // Wait for all consumers.
    for (auto& t : consumers) {
        t.join();
    }

    std::cout << "\nAll producers and consumers finished.\n";
}
```

2. Dining Philospher Problem
- Imagine 5 philosophers sitting around a circular table.
- There are 5 forks, one between each pair of philosophers.
- Each philosopher needs two forks to eat:
             P0
         F0       F1
       P4           P1
        F4         F2
          P3     P2
              F3
```cpp
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore>
#include <thread>
#include <vector>

constexpr int NUM_PHILOSOPHERS = 5;

// There are 5 forks.
std::counting_semaphore<1> forks[NUM_PHILOSOPHERS]{
    1, 1, 1, 1, 1
};

// Allow at most 4 philosophers to compete for forks.
std::counting_semaphore<4> room(NUM_PHILOSOPHERS - 1);

// Only used to prevent output from getting mixed together.
std::mutex coutMutex;


// ---------------------------------------------------------
// Utility function for printing
// ---------------------------------------------------------

void print(const std::string& message) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cout << message << '\n';
}


// ---------------------------------------------------------
// Philosopher
// ---------------------------------------------------------

void philosopher(int id) {
    const int leftFork = id;
    const int rightFork = (id + 1) % NUM_PHILOSOPHERS;

    std::mt19937 rng(std::random_device{}() + id);

    for (int meal = 1; meal <= 5; ++meal) {
        // -------------------------------------------------
        // THINK
        // -------------------------------------------------

        print("Philosopher " + std::to_string(id) +
              " is thinking.");

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100 + rng() % 200));


        // -------------------------------------------------
        // HUNGRY
        // -------------------------------------------------

        print("Philosopher " + std::to_string(id) +
              " is hungry.");


        // -------------------------------------------------
        // Enter the room.
        //
        // At most 4 philosophers can reach the fork
        // acquisition stage simultaneously.
        // -------------------------------------------------

        room.acquire();


        // -------------------------------------------------
        // Pick up left fork
        // -------------------------------------------------

        forks[leftFork].acquire();

        print("Philosopher " + std::to_string(id) +
              " picked up left fork " +
              std::to_string(leftFork));


        // -------------------------------------------------
        // Pick up right fork
        // -------------------------------------------------

        forks[rightFork].acquire();

        print("Philosopher " + std::to_string(id) +
              " picked up right fork " +
              std::to_string(rightFork));


        // -------------------------------------------------
        // EAT
        // -------------------------------------------------

        print("Philosopher " + std::to_string(id) +
              " is EATING.");

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100 + rng() % 200));


        // -------------------------------------------------
        // Put down forks
        // -------------------------------------------------

        forks[rightFork].release();
        forks[leftFork].release();

        print("Philosopher " + std::to_string(id) +
              " put down both forks.");
        // Leave the room.
        room.release();
    }
}


// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

int main() {
    std::vector<std::thread> philosophers;

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& philosopher : philosophers) {
        philosopher.join();
    }

    std::cout << "\nAll philosophers have finished eating.\n";
}
```