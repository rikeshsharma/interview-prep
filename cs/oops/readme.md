# Object Oriented Programming

### Core

1. Classes & Objects
2. Encapsulation
3. Abstraction
4. Inheritance
   - Single, multiple, multilevel, hierarchical
   - Multiple inheritance issues
5. Polymorphism
   - Compile-time polymorphism
   - Runtime polymorphism
   - Function overloading
   - Function overriding
   - Virtual functions
   - Pure virtual functions

#### C++ Specific OOP
6. Virtual Functions & Virtual Destructors
7. Abstract Classes & Interfaces
8. Upcasting & Downcasting
9. Object Slicing
10. Virtual Table (vtable) & Virtual Pointer (vptr)
11. Constructor & Destructor Behavior with Inheritance
12. Multiple Inheritance & Diamond Problem
  - Virtual inheritance

### Advanced

13. Composition vs Inheritance
- “is-a” vs “has-a”
- Prefer composition over inheritance
- When inheritance is actually appropriate
- Runtime vs compile-time polymorphism

14. Interfaces & Abstract Classes
- Pure virtual functions
- Virtual destructors
- Interface design
- Abstract base classes
- Multiple inheritance for interfaces

15. Dependency Injection (DI)
- Constructor injection
- Dependency inversion
- Why DI improves testability and flexibility
- DI using interfaces/references/smart pointers

16. Immutability & const Correctness
- const objects and methods
- const references/pointers
- Designing immutable objects
- Benefits for thread safety and maintainability

17. RAII & Resource Ownership
- RAII principle
- Ownership vs lifetime
- Resource management
- Exception safety
- Custom RAII wrappers

18. Smart Pointers
- std::unique_ptr
- std::shared_ptr
- std::weak_ptr
- Ownership semantics
- make_unique / make_shared
- Circular references
- When not to use smart pointers

19. Move Semantics
- Lvalues vs rvalues
- Rvalue references (&&)
- std::move
- Move constructor / move assignment
- Copy vs move
- Perfect forwarding
- std::forward
- Moved-from objects

19. Rule of 3 / 5 / 0
- Destructor
- Copy constructor
- Copy assignment
- Move constructor
- Move assignment
- Rule of Zero
- Why resource-owning classes need special member functions

20. Composition vs Inheritance
21. Aggregation vs Composition
22. Dependency Injection
23. Programming to an Interface
24. SOLID Principles
25. Coupling vs Cohesion
26. Open/Closed Principle & Dependency Inversion
27. Designing extensible and maintainable classes