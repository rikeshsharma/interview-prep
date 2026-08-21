# Decorator

- It is a structural design pattern that attaches new behavior to
existing object by placing these object into special wrapper object
that contain the behavior.
- Add additional behavior/responsibility to an object dynamically
by wrapping it inside another object.

- inheritance has several serious caveats
  1. Inheritance is static.
  2. Subclasses can have just one parent class. (not in c++ but in other programing langs)
- Aggregation or Composition  instead of Inheritance overcomes these caveats.

- Use the Decorator pattern when we need to be able to assign extra behaviors
to objects at runtime without breaking the code that uses these objects.
- The Decorator lets you structure your business logic into layers, create 
a decorator for each layer and compose objects with various combinations 
of this logic at runtime.
- The client code can treat all these objects in the same way, 
since they all follow a common interface.

### Remember

             Component
                ↑
        ┌───────┴────────┐
        │                │
 ConcreteComponent    Decorator
                         ↑
                  ┌──────┴──────┐
                  │             │
             Decorator A    Decorator B

And especially:
```cpp
class Decorator : public Component {
protected:
    Component* component_;
};
```
The decorator:
1. is a Component
2. contains a Component
3. delegates to the contained Component
4. adds its own behavior