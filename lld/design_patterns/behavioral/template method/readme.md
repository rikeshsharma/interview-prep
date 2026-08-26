# Template Method

-  It is a behavioral design patter that lets us define the structure/skeleton of
algorthim in the base/super class but allow the subclass to override these 
individual algorithm methods

- **Template Method** = fixed algorithm + customizable steps
             FIXED
               ↓
        ┌───────────────┐
        │   Step A      │
        │   Step B      │ ← customizable
        │   Step C      │ ← customizable
        │   Step D      │ ← customizable
        │   Step E      │
        └───────────────┘
               ↑
             FIXED

- **Hooks** = A hook is a method that has a default implementation in the base class, but subclasses can optionally override it.

### When to use

1. Multiple classes follow the same algorithm
2. The algorithm order must not change
3. You want to eliminate duplicated algorithm code

**Note** Template Method strongly demonstrates:
Hollywood Principle: "Don't call us, we'll call you."
The base class controls the process.


### Structure

```cpp
class Base {
public:

    void templateMethod() {
        step1();
        step2();
        step3();
        step4();
    }

protected:

    virtual void step2() = 0;
    virtual void step4() = 0;

    void step1() {
        // common implementation
    }

    void step3() {
        // common implementation
    }
};

class Derived : public Base {
protected:

    void step2() override {
        // derived-specific implementation
    }

    void step4() override {
        // derived-specific implementation
    }
};

class Derived : public Base {
protected:

    void step2() override {
        // derived-specific implementation
    }

    void step4() override {
        // derived-specific implementation
    }
};

Derived obj;
obj.templateMethod();
```