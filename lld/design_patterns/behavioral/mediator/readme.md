# Mediator

- It is a behavioral design pattern, that reduces the direct
communication between multiple objects by making them communicate
through a central object called Mediator.

### Structure of mediator

1. Mediator
2. Concrete Mediator
3. Colleagues
4. Concrete Colleagues

- Colleague
    │
    │ notify()
    ↓
Mediator
    │
    │ coordinates
    ↓
Other Colleagues

**example**

- Alice
  │
  │ send("Hello")
  ↓
ChatRoom
  │
  ├────→ Bob
  ├────→ Charlie
  └────→ David

- A mediator should coordinate communication, not necessarily contain all business logic.
- Sole purpose of mediator should be mediation.

### Obsever vs Mediator

- Observer: One object's state changes → notify interested observers.
- Mediator: Multiple objects need to communicate → centralize their interaction.

### When should we use Mediator

1. Many objects communicate with each other.
2. Objects have too many dependencies
If you see classes containing many references like:
  ```cpp
  class Component {
      A* a;
      B* b;
      C* c;
      D* d;
      E* e;
  };
  ```
Mediator might be useful.
3. Communication rules are complicated
For example:
If A sends X:
    notify B

If B is busy:
    notify C

If C is unavailable:
    queue message

If A is admin:
    notify everyone
This coordination can belong in the mediator.

