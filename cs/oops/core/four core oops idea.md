# Core OOPs 

1. Encapsulation
2. Abstraction
3. Inheritance
4. Polymorphism

### Encapsulation

- [Encapsulation](https://chatgpt.com/share/6a9446a9-6970-83ee-a3e8-96b1634437f2)
- Encapsulation means bundling data and the operations that
manipulate that data into a single unit, while controlling
how the outside world can access that data.
-  that entity is usually a class
- Access modifiers of class helps to acheive this

### why do we need encapsulation

-  To protect the object invariants
  - An **invariant** is a condition that should always 
    remain true for a valid object.
    example balance of Bank class should always be >= 0
  - Encapsulation ≠ Just making private 
    - Its about protecting the invariants of class
- Encapsulation is about controlling access to state and
  behavior so that the object maintains its invariants

- The class decides:
  1. What is exposed
  2. What is hidden
  3. How state can be modified

                 Class
        ┌─────────────────────┐
        │                     │
        │   Internal State    │
        │   ───────────────   │
        │   private data      │
        │                     │
        │   Internal Logic    │
        │   ───────────────   │
        │   private helpers   │
        │                     │
        │─────────────────────│
        │   Public Interface  │
        │                     │
        │   deposit()         │
        │   withdraw()        │
        │   getBalance()      │
        └─────────────────────┘
                  ↑
                  │
             Outside code

- `private` : Accessible only from the class's member functions and friends
- `protected`: Accessible from: the class itself, derived classes, friends
- `public` : Accessible from anywhere
- "Private + good getter/setter = good encapsulation"

### Encapsulation vs abstraction

- Encapsulation: How do we control access to internal state/implementation?
Bundling data + behavior together and controlling access to them.

- Abstraction: What does the user need to know, and what unnecessary implementation details can we hide?
Exposing a simplified interface and hiding unnecessary implementation complexity.

| Encapsulation | Abstraction |
|---|---|
| Controls access | Hides complexity |
| Protects state | Exposes essential behavior |
| `private`, `protected`, `public` | Interfaces / APIs |
| "Who can access this?" | "What does the user need to know?" |

- Encapsulation allows implementation details to change without affecting clients. 
(a vector data member can later change to list, deque etc)

### Abstraction

- Abstraction is designing a stable, minimal interface that exposes the behavior 
clients need while hiding implementation details that are subject to change. This 
reduces coupling and allows implementations to evolve independently of their clients.
- "Tell me WHAT I can do, not HOW you do it."
- In C++, it can be achieved using classes, access control, and especially 
abstract classes with pure virtual functions.

### Polymorphism

- [Polymorphism](https://chatgpt.com/share/6a945fa3-7db8-83ee-8dd9-4cdc8247378e)
- Polymorphism = one interface, multiple implementations
- Types of polymorphism
  1. compile time polymorphism
    - decision is made by compiler at compile time
      - Function overloading 
      - Operator overloading
      - Templates
  2. runtime polymorphism
    - decision is made during runtime: primarily achieved by `virtual`
      - Function overriding

- Static Binding vs Dynamic Binding
  - static binding: function call is resolved at compile time
  ```cpp
    class Base {
    public:
        void foo() {
            cout << "Base";
        }
    };
    class Derived : public Base {
    public:
        void foo() {
            cout << "Derived";
        }
    };
    Base* p = new Derived();
    p->foo(); // output is "Base" as foo is not virtual : static binding
              // if foo was virtual and overrided in 
              // Derived then output would be "Derived" : dynamic binding
  ```
  - dynamic binding: function call is resolved at runtime

- How does the virtual dispatch actually works ?
  - the compiler sets up an indirect lookup mechanism that allows the program 
    to select the correct function at runtime based on the actual object type.
    This is popularly known as the dynamic binding or late binding
  1. The Virtual Table (vtable)
    - When a compiler encounters a class containing at least one virtual function, 
      it constructs a static array of function pointers specifically for that class. 
      This is called the vtable.

    - Base Class vtable: Stores the memory addresses of the 
                virtual functions defined in the base class

    - Derived Class vtable: Inherits the base class's vtable 
                layout. If the derived class overrides a 
                virtual function, the compiler replaces 
                (overwrites) the base function's address 
                with the address of the derived class's 
                function. If it does not override it, the 
                slot continues to point to the base class 
                implementation.
  
  2. The Virtual Pointer (vptr)
    - Every time you instantiate an object of a class that has virtual functions, 
      the compiler secretly inserts a hidden pointer into the object's memory 
      layout. This is called the vptr.
  
  - When a Base object is created, its vptr points to the Base class vtable.
  - When a Derived object is created, its vptr points to the Derived class vtable.

### What exactly triggers runtime polymorphism?
1. A virtual function
  - `virtual void foo();`
2. Calling through a polymorphic interface
  - `Base* p = new Derived(); p->foo();` or
  - `Base& r = derived; r.foo();`

- Can a virtual function be static?
  - No, static member functions don't operate on an object and don't have a this pointer.
  - Virtual dispatch requires an object/dynamic type.

- Can constructors be virtual?
  - No, A constructor creates the object; dynamic dispatch requires an already-existing object's dynamic type.

### Inheritance

- Inheritance is an OOP mechanism where a new class (derived class) 
acquires properties and behavior from an existing class (base class)
- IS-A relationship
  1. Code reuse
  2. Polymorphism
- Types of inheritance
  1. Single inheritance
  2. Multilevel inheritance
  3. Hierarchical inheritance
  4. Multiple inheritance
  5. Hybrid inheritance : combining above types
- we can inherit using `public`, `protected` and `private` qualifiers
- A Derived object contains a Base subobject.

| Base Member | **Public Inheritance** `class D : public B` | **Protected Inheritance** `class D : protected B` | **Private Inheritance** `class D : private B` |
|---|---|---|---|
| `public` | `public` | `protected` | `private` |
| `protected` | `protected` | `protected` | `private` |
| `private` | Inaccessible directly | Inaccessible directly | Inaccessible directly |
| **Relationship** | **Derived IS-A Base** | Usually implementation relationship | Usually implementation relationship |
| **Common usage** | **Most common** | Less common | Less common |

- Private members of the base class are still part of the base subobject,
but the derived class cannot directly access them.

- Upcasting
- Downcasting

### Diamond Problem and Virtual Inheritance
       A
      / \
     B   C
      \ /
       D
```cpp
class A {
public:
    int x;
};

class B : public A {};
class C : public A {};
class D : public B, public C {};

D d;
// d.x = 10; // ambiguous because which A::x ?
```

- Virtual inheritance solves the diamond duplication.
```cpp
class A {
public:
    int x;
};

class B : virtual public A {};
class C : virtual public A {};

class D : public B, public C {};
D d;
d.x = 10;
```
- There is only one shared A subobject
- With virtual inheritance, the most-derived class (the grandmost child) is responsible for constructing the virtual base

### Compile time template polymorphism

- Compile-time polymorphism means that the implementation to execute is determined during 
compilation rather than through runtime dispatch. C++ templates are a primary mechanism 
for this. The compiler generates code based on the concrete types, and calls can often be 
statically resolved and inlined.


### CRTP Curiously Recursive Template Pattern

- CRTP, or Curiously Recurring Template Pattern, is a pattern where a derived class passes 
itself as a template parameter to its base class, such as `class Derived : public Base<Derived>`. 
The base can then cast this to Derived* and call derived functionality. Since the derived type
is known at compile time, this provides static polymorphism without virtual dispatch.
