# Mutex and Locks

- #include <thread> : standard library for threads in c++
- #inlcude <mutex> : standard library for mutual exclusion implementation
                     for a given code block in ++
                  : The mutex provides mutual exclusion.
                  : everything inside the m.lock <---> m.unlock is
                  executed by one thread at a time. And the block of
                  code remains with that thread untill the m.unlock is 
                  encountered by that thread. 
std::mutex m;
m.lock();
m.unlock();
- std::lock_guard<std::mutex> lock(m) : RAII object for acquiring and release mutex
                                      when lock goes out of scope.

- std::unique_lock<std::mutex> lock(m) : RAII object for acquiring and release of mutex
                                        but allows flexible lock and unlock
- can call lock.lock(), lock.unlock(), std::unique_lock<std::mutex> lock(m, std::defer_lock)
- std::unique_lock<std::mutex> lock(m, std::try_to_lock) : try to acquire lock without blocking
```cpp
std::unique_lock<std::mutex> lock(m, std::try_to_lock);

if (lock.owns_lock()) {
    // Successfully acquired mutex
}
else {
    // Mutex was already locked
}
```
1. What's the difference between lock_guard and unique_lock?
- lock_guard is a simple RAII wrapper that acquires a mutex on construction 
and releases it on destruction. It doesn't allow manual unlocking or deferred 
locking. unique_lock is more flexible: it can defer locking, manually unlock 
and relock, use try_lock, transfer ownership, and is required by condition_variable::wait() 
because the wait operation needs to temporarily release and then reacquire the mutex.
