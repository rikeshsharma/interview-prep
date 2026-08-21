# Proxy

- a proxy is an object that stands in front of another object.
- proxy and real object implements the same interface.

### Why proxy
  1. Access Control
  2. Lazy Initialization
  3. Logging
  4. Caching
  5. Remote objects

### Structure

        Subject Interface
           /         \
          /           \
       Proxy       RealSubject
         |
         |
      forwards
         |
         ↓
    RealSubject

Client
- Only knows about Subject.
- doesn't need to know that a RealSubject exists behind the proxy.

### Proxy Types

1. Virtual Proxy: Controls expensive creation
2. Protection Proxy: Controls access
3. Remote Proxy: Represent object somewhere else
4. Caching Proxy: Stores previous results