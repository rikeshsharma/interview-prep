# Constructor

### Types of Constructor

1. Default constructor
  - A default constructor is a constructor that can be called without providing any arguments
  - Default constructor ≠ constructor with default arguments, although the latter can be callable with zero arguments
    ```cpp
    class A {
    public:
        A(int x = 10) {} // not a default constructor
    };

    A a;  // calls A(10)
    ```
  - If we don't declare any constructor, C++ may implicitly generate a default constructor
    - If we do not initialize the datamember, #1they are not-reliably-
      {given this datamember[1]
      do not recursively(datamember[2] of class that the previous datameber[1] is type of) 
      have default constructor}
      -initialized for a local automatic object.

  - Global Object -> they have static storage duration, data members are zero-initialized before program starts
  - Local Automatic Object -> not reliably initialized given #1 hold
  - Dynamically object with just `new` 
    `Employee* e = new Employee` -> not reliably initialized given #1 hold
  - Dynamically allocated object with `new Employee()``
    `Employee* e = new Employee()` -> is zero-initialized

  - Does this happen only for built-in types?
  - No, all for types that do not have default initializer
    - built in type do not have default initializer
    - any class containing these and not providing default initialization
  
  1. In class initialization
  ```cpp
  class Employee {
    int id = 0;
  };
  ```
    - Unless a constructor explicitly initializes id differently, initialize it with 0

  2. Constructor initializer list
  ```cpp
  class Employee {
    int id;
  public:
    Employee() : id(0) {}
  };
  ```
  - the constructor explicitly initializes id to 0

2. Parameterized Constructor

  - takes one or more argument and uses them to initialze an object
    - prefer initialization list

3. Copy Constructor

  - It creates a new object from the existing object of the class
  - signature: `ClassName(const ClassName& other)`
  - usage: `ClassName object2(object1)`, `ClassName object2 = object1`
    - Employee e2 = e1;  // COPY CONSTRUCTOR since e2 does not exist yet
    - e2 = e1;            // COPY ASSIGNMENT since e2 already exists

  - const is used in signature because we should be able to copy from a const object
  - &: because we take reference other wise infinite recursion will occur

  - compiler can generate a copy constructor
    - compiler-generated-copy-constructor does memberwise-copy(every member copy constructor is called)
    - for pointers member variable it does **shallow copy** (copies the address stored from the target pointer)
      - if this is unintentional, it may lead to double-free or undefined behavior
      - thats why having a pointer member variable requires careful copy semantics
  
  - we can define for **deep copy**
  ```cpp
  class Buffer {
    int* data;

  public:
      Buffer(int value)
          : data(new int(value)) {}

      Buffer(const Buffer& other)
          : data(new int(*other.data)) {}

      ~Buffer() {
          delete data;
      }
  };
  ```
  - copy constructor can be explicitly deleted
  `ClassName(const ClassName&) = delete`
  - similarly copy assignment can be explicitly deleted
  `ClassName& operator=(const ClassName&) = delete`
  -  explicitly request compiler generated copy constructor
  `ClassName(const ClassName&) = default`

  - called when
    - direct initialization: `ClassName e1(e2)`
    - copy initialization: `ClassName e1 = e2`
    - passing by value
    - returning by value: by **copy elison**: a C++ compiler optimization that stops the program 
                                          from making *extra* copies or moves of objects.
                                          - construct returned objects directly in the memory 
                                          space of the calling function to avoid making copies
                                          - 2 types : Return Value Optimization (RVO) and
                                                      Named Return Value Optimization (NRVO)
    - object slicing:
    ```cpp
      class Animal {
      public:
          int age;
      };

      class Dog : public Animal {
      public:
          int breed;
      };

      Dog d;

      Animal a = d;
    ```
    - The Animal object a contains only the Animal portion.
    - The Dog portion is sliced away.
    - happens for member function as well
    - Therefor, passing polymorphic objects by value can therefore be dangerous.
      - prefer
        `void foo(const Animal& animal);`
        than
        `void foo(Animal animal);`
        when polymorphism is intended

4. Move Constructor

  - transfers ownership of resources (like dynamically allocated memory)
    from a temporary (rvalue) object directly to a new object.
  - it simply "steals" the pointers and leaves the temporary object empty.
  - signature: `ClassName(ClassName&&)`
  - usage: `ClassName object2(object1)`, `ClassName object2 = object1`

  - std::move() doesn't move anything by itself.
  - std::move is a cast, not a move operation.
  - essentially converts the expression into an rvalue 
    so that move operations can be selected.
  
  - Employee e2 = std::move(e1);  // MOVE CONSTRUCTOR since e2 does not exist yet
          - e2 = std::move(e1);            // MOVE ASSIGNMENT since e2 already exists

5. Delegating Constructor

  - calls another constructor from the same class inside its initializer list
  - cuts down code duplication, if multiple constructor share the same setup logic
    `Player() : Player(0) {} // Calls the parameterized version`
    `Player(int s) { score = s; }`

6. Conversion/Explicit Constructor

  - `explicit` prevents unwanted implicit conversions through that constructor.
  - works for one parameter or
  - multiple parameters if all but the first have default arguments

7. Copy assignment

  - signature: `ClassName& operator=(const ClassName&)`
  - other things are similar to copy constructor

8. Move assignment
  - signature: `ClassName& operator=(ClassName&& other) noexcept`
  - other things are similar to move constructor
  - `noexcept`: is not mandatory but we use it
    - Because standard containers can make better decisions when move operations are noexcept
      - `std::vector<T> v;` When vector needs to grow, it may need to move existing elements to new storage.
      - If `T(T&&) noexcept`: then vector knows the move won't throw and can safely use it.
      - But if your implementation genuinely cannot throw, you generally want `ClassName& operator=(ClassName&& other) noexcept;`

### Destructor

- It is a special member function that is automatically called when an object's lifetime ends
- Its primary use is to release resources owned by the object
- signature: `~ClassName()`
-  can have only one destructor per class

- virtual destructor : If the class is to be used polymorphically then we define
  `virtual ~ClassName() = default` because this reliably destroys the derived
  class object using base class pointer

- private destructor : When a destructor is declared private, instances of the class cannot be destroyed by external code
  - enforces heap allocation
  - disable standard delete usage
  - prevent standard inheritance
- is deliberately used to control the lifecycle of an object and restrict memory management
```cpp
class ReferenceCounted {
private:
    int refCount = 0;
    ~ReferenceCounted() {} // Cannot be deleted externally

public:
    void AddRef() { refCount++; }
    void Release() {
        if (--refCount == 0) {
            delete this; // Authorized to call its own private destructor
        }
    }
};
```

```cpp
class HeapOnly {
private:
    ~HeapOnly() {} // Private destructor prevents stack creation

public:
    void destroy() {
        delete this; // Allowed internally
    }
};

int main() {
    // HeapOnly obj; // COMPILE ERROR: Destructor is private
    
    HeapOnly* ptr = new HeapOnly(); // Allowed
    // delete ptr;   // COMPILE ERROR: Cannot access destructor
    
    ptr->destroy();  // Allowed: Properly cleans up the object
}
```

- pure virtual destructor: to make a class abstract when you don't have any other virtual 
  functions that can be made pure virtual, while still ensuring safe, polymorphic deletion of derived objects
  - It must have a destructor body
```cpp
// Abstract Base Class
class Base {
public:
    // 1. Declaration of the pure virtual destructor
    virtual ~Base() = 0; 
};
// 2. MANDATORY: Definition of the pure virtual destructor
Base::~Base() {
    std::cout << "Base destructor called\n";
}
```
  - To Create an Abstract Base Class
  - To Guarantee Safe Polymorphic Deletion
