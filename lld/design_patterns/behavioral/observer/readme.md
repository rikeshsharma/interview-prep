# Observer

- It is a behavioral design pattern that lets us define a
  - subscription mechanism 
  - to notify multiple objects about any  event that 
  - happens to the object they are observing.

- One object changes, and multiple other objects need to automatically know about that change.

                Subject(Observable)
                        |
                        |
              +---------+----------+
              |         |          |
        Observer1   Obsercer2   Observer3

      Subject------|> Observer<Interface>
     Add Observer            ^
     Remove Observer         |
      On Event               |
                        ConcreteObserver

### Type of notification

1. Push : The Subject sends the changed data directly.
2. Pull : The Subject only says: "Something changed." 
Then the Observer asks the Subject for the information it needs.
This can be useful when observers need different pieces of information.

### When to use

1. Multiple objects depend on one object's state.
2. You don't want the Subject tightly coupled to observers.
3. Observers can be added/removed dynamically.

### Observer vs Subject
A useful mental model:
| Component | Responsibility |
|---|---|
| **Subject** | Maintains state |
| **Subject** | Maintains observers |
| **Subject** | Notifies observers |
| **Observer** | Receives notification |
| **Concrete Observer** | Decides what to do after notification |

Subject = "Something changed."
Observer = "What should I do about it?"

### Issue

- Lifetime issue of observer, if observer is destroyed without
removing/detaching itself from observerlist, and subject tries to 
notify then undefined behavior or crash can occurr.

- So a real implementation needs to think carefully about ownership and lifetime.
- In production C++, depending on ownership semantics, you might use:
```cpp
std::weak_ptr
std::shared_ptr
```


### Aside

Chromium C++ uses several observer mechanisms, but the most important 
one to understand is base::ObserverList. It is essentially a production-grade 
infrastructure for the Observer pattern, with additional handling for things that
become tricky in real C++ code: object lifetime, observers being added/removed
during notification, and safe iteration.

1. base::ObserverList: It has semantics around:
  - adding observers
  - removing observers
  - iteration
  - observers modifying the list during notification
  - observer lifetime assumptions
  - notification behavior
2. base::CheckedObserver: This is designed to help detect cases where an observer
 is destroyed without being removed from the ObserverList. (inherit the observer class from this)
3. base::ScopedObservation: Instead of manually doing:
subject->AddObserver(this);
and remembering:
subject->RemoveObserver(this);
this allows scoped observation object manage that relationship.