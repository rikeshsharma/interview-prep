# Flyweight

- It is a structural design pattern that when there are huge number of objects, 
but many of those objects contain the same data, so instead of storing that 
data repeatedly, allows sharing it.
- also known as cache.
- reduce memory usage.

We divide an object's data into two categories.
1. Intrinsic state: Data that is shared between object.
2. Extrinsic state: Data that is unique to particular usage of the object.

Flyweight                    Client
    ↓                           ↓
shared state               unique state
