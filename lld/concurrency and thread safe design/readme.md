# Concurrency and Thread Safe

1. [Process](../../cs/operating%20system/process.md)
2. [Thread](../../cs/operating%20system/thread.md)
3. [InterProcess Communication](../../cs/operating%20system/interprocess_communication.md)
4. [Synchornization](../../cs/operating%20system/synchronization.md)
5. [Mutex and Locks](../../cs/operating%20system/mutex%20and%20locks.md)
6. [Semaphores](../../cs/operating%20system/semaphores.md)
7. [Deadlock](../../cs/operating%20system/deadlock.md)

### Thread Safe Class Design
 
- [Thread Safe Class Design](https://chatgpt.com/share/6a93a6f8-0a2c-83e9-b3cd-3bbb141c7bf4)

---

### Important topics

| # | Topic | Priority |
|---|---|---|
| 1 | **Threads & Thread Lifecycle** | ⭐⭐⭐⭐⭐ |
| 2 | **Race Conditions & Data Races** | ⭐⭐⭐⭐⭐ |
| 3 | **Mutexes & Locking** | ⭐⭐⭐⭐⭐ |
| 4 | **Condition Variables** | ⭐⭐⭐⭐⭐ |
| 5 | **Producer–Consumer / Blocking Queue** | ⭐⭐⭐⭐⭐ |
| 6 | **Deadlocks, Starvation & Livelock** | ⭐⭐⭐⭐⭐ |
| 7 | **Thread-Safe Class Design** | ⭐⭐⭐⭐⭐ |
| 8 | **Thread Pools** | ⭐⭐⭐⭐⭐ |
| 9 | **Atomics (`std::atomic`)** | ⭐⭐⭐⭐⭐ |
| 10 | **C++ Memory Model & Basic Memory Ordering** | ⭐⭐⭐⭐ |
| 11 | **semaphores** | ⭐⭐⭐⭐ |
| 12 | **Dining Philospher** | ⭐⭐⭐⭐ |

- Threads
-    ↓
- Race Conditions
-    ↓
- Mutex + RAII Locking
-    ↓
- Condition Variables
-    ↓
- Producer–Consumer
-    ↓
- Deadlocks
-    ↓
- Thread-Safe Classes
-    ↓
- Thread Pool
-    ↓
- Atomics
-    ↓
- C++ Memory Model

### classic interview problems

- Producer–Consumer
- Readers–Writers
- Dining Philosophers
- Thread-safe Singleton
- Thread-safe Queue
- Thread Pool

---

### Full Syllabus (Not required for interview)

| # | Topic |
|---|-------|
| 1 | **Threads & Thread Lifecycle** |
| 2 | **Race Conditions & Data Races** |
| 3 | **Mutexes & Locks** |
| 4 | **RAII Locking (`lock_guard`, `unique_lock`, `scoped_lock`)** |
| 5 | **Condition Variables** |
| 6 | **Producer–Consumer Problem** |
| 7 | **Deadlocks** |
| 8 | **Deadlock Prevention & Avoidance** |
| 9 | **Thread-Safe Class Design** |
| 10 | **Thread Pools** |
| 11 | **Atomics & `std::atomic`** |
| 12 | **Memory Ordering** |
| 13 | **C++ Memory Model / Happens-Before** |
| 14 | **`future`, `promise`, `async`** |
| 15 | **`std::jthread` / Thread Cancellation** |
| 16 | **Read-Write Locks (`shared_mutex`)** |
| 17 | **Semaphores** |
| 18 | **Barriers / Latches** |
| 19 | **Lock-Free / Wait-Free Concepts** |
| 20 | **Common Concurrency Problems** |

### classic interview problems

1. Producer–Consumer
2. Readers–Writers
3. Dining Philosophers
4. Thread-safe Singleton
5. Thread-safe Queue
6. Thread Pool

### Syllabus

Phase 1 — Fundamentals
1. Process vs Thread
2. Thread lifecycle
3. Creating/joining/detaching threads
4. Race conditions
5. Data races
6. Critical sections
7. Thread-safe vs thread-unsafe code
Phase 2 — Locks
8. Mutex
9. lock_guard
10. unique_lock
11. scoped_lock
12. try_lock
13. Multiple mutexes
14. Lock granularity
15. Lock contention
Phase 3 — Condition Variables
16. Condition variables
17. wait()
18. wait(lock, predicate)
19. notify_one
20. notify_all
21. Spurious wakeups
22. Producer–consumer
Phase 4 — Deadlocks
23. What is deadlock?
24. Four Coffman conditions
25. Lock ordering
26. Deadlock prevention
27. Deadlock avoidance
28. std::lock
29. std::scoped_lock
30. Starvation
31. Livelock
Phase 5 — Thread-safe Design
32. Designing thread-safe classes
33. Protecting invariants
34. Mutable shared state
35. Const methods + synchronization
36. Thread-safe queues
37. Thread-safe caches
38. Thread-safe Singleton
39. Exception safety with locks
Phase 6 — Thread Pools
40. Worker threads
41. Task queue
42. Worker lifecycle
43. Shutdown
44. Graceful shutdown
45. Task submission
46. Returning results
47. Thread-pool implementation
Phase 7 — Atomics
48. std::atomic
49. Atomic read/write
50. fetch_add
51. compare_exchange
52. CAS
53. Spinlocks
54. Atomic flags
55. Atomic vs mutex
Phase 8 — C++ Memory Model
56. C++ memory model
57. Happens-before
58. Synchronizes-with
59. Sequential consistency
60. Acquire
61. Release
62. Relaxed ordering
Phase 9 — Higher-level synchronization
63. future
64. promise
65. async
66. packaged_task
67. shared_mutex
68. counting_semaphore
69. latch
70. barrier
71. jthread
72. stop_token
Phase 10 — Interview Problems
73. Producer–Consumer
74. Readers–Writers
75. Dining Philosophers
76. Thread-safe Queue
77. Thread Pool
78. Rate Limiter
79. Concurrent Cache
80. Blocking Queue
81. Parallel Counter
82. Ordered execution between threads
83. Print ABCABCABC... using 3 threads
84. Alternate odd/even printing
85. Implement a thread-safe Singleton

[Concurreny and Thread Safe Design Syllabus](https://chatgpt.com/share/6a9024a5-be90-83e9-8b01-54621802824d)