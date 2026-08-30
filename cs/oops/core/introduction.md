# Basic OOPs

### Classes

- A class is a user-defined type that combines data and behavior
- It defines:
  - Data → member variables
  - Behavior → member functions
  - Access rules → `private`, `protected`, `public`

### Object

- An object is an instance of class

### Class vs Object

| Class | Object |
|---|---|
| Blueprint/type | Instance of the type |
| Defines structure, behavior and access rules | Has actual state |
| Doesn't represent a particular entity | Represents a particular entity |
| `class BankAccount` | `BankAccount account1` |
| One class can create many objects | Each object has its own non-static data |

### Inside Object

- The object contains data members
- Member functions are not copied in every object
+----------------+
| e1:            |
|  id.           |
|  salary        |
|  print()  ❌   |
+----------------+
- Instead, member functions are generally shared code,
and the compiler passes an implicit `this` pointer when
we call them
- so when we do 
  `Employee e; e.setId(10);` compiler does something like
  `Employee::setId(&e, 10);`

### Access Modifiers

1. `private`: Only the class's member functions and friends can directly access it
2. `public`: Accessible from outside
3. `protected`: Accessible from:
  - the class itself
  - derived classes
  - friends

### Constructor

- A constructor initializes an object
 - initializer lists: it initializes the data member
 - constructor body initialisation: it initializes the data member first 
    and then performs assignment inside the constructor body

- This distinction matters particularly for:
  - const members
  - references
  - data members whose type do not have default constructors
  - performance/design correctness

### Destructor

- constructor
     ↓
 object exists
     ↓
 destructor <- When an object is removed from memory, it destructor is called
     ↓
 object destroyed

### Stack and Heap Object

1. Automatic/local/Scope/Stack object
  - automatically destroyed when it goes out of scope
2. Dynamically allocated/Heap object
  - programmer is responsible for destruction

### Class's object can contain other Class type object

- called Composition

### Class can inherit from other Class

- Called Inheritace

### Is-A vs Has-A Relationship

```cpp
class Engine {
};
class Vehicle {
};
class Car : public Vehicle {
private:
    Engine engine;
};
```

- Car **is a** Vehicle : used to show inheritance relationship
- Car **has a** Engine : used to show composition relationship

- For modern C++ design, composition is often preferred over inheritance
  unless inheritance represents a genuine substitutable relationship
