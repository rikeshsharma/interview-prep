# Deadlock

- There are 2 locks, A and B.
- Process 1 has lock A and is waiting to acquire lock B
- Process 2 has lock B and is waiting to acquire lock A
- None of the Process can proceed because they are waiting 
for each other.
- This situation is called Deadlock.
- A deadlock is a situation where a set of processes/threads 
are permanently blocked because each one is waiting for a 
resource held by another process/thread in the same set.

### Coffman coditions

- These are the set of 4 condition, which when happen simultaneously,
creates a Deadlock.
  1. Mutual Exclusion
  2. Hold and Wait
  3. Non Preemptive: A resource can not be forcible take from a process/thread
                     that is holding it.
  4. Circular wait: There is circular chain of waiting.
- All four conditions must exist simultaneously for a deadlock to occur.

**-To prevent deadlock, break at least one of the four conditions-**

### Starvation
- A thread keeps getting denied access to a resource while other 
threads continue making progress.
- Unfair scheduling/resource allocation

### How to prevent Deadlocks

1. Lock ordering: Order the lock in such a way that lock ordering is not possible
  - use std::lock, std::scoped_lock
2. Do not hold the lock unnecessarily, smaller the amount for which the lock is held
    easier it is to avoid contention.
3. Use c++ std::try_lock

### How to detect Deadlocks

1. Using Resource allocation graphs
          T1 ────wants───> B
          ↑                │
       owned by          owned by
          │                ↓
          A <───wants──── T2

2. Using Wait for graph
              T1 → T2
              ↑    ↓
              └────┘

Cycle means **Deadlock**

### Banker's Algorithm

- The OS considers:
    - Available resources
          +
    - Current allocations
          +
    - Maximum future requirements
- and determines whether granting a request leaves the system in a safe state.
- If safe:
  - Grant request
- If unsafe:
  - Delay request
We don't necessarily have a deadlock yet.
We're simply avoiding entering a state that could lead to deadlock.

### Recovery from Deadlock

1. Terminate the process
2. Preemptively take the resource
3. Rollback the process to earlier safe state

### Differences

1. Prevention
    ↓
Never allow circular wait

2. Avoidance
    ↓
Check whether granting resource is safe

3. Detection
    ↓
Allow it
    ↓
Detect cycle/deadlock

4. Recovery
    ↓
Kill/rollback/preempt something