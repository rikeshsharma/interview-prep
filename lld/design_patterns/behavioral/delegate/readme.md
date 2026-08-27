# Delegate

- It is a behavioral design pattern that statest that
instead of doing the job myself, I will give this job
to some object that knows how to do it.
- It is not a classic GoF 23 Design Pattern
- It is more of a general object-oriented design technique/pattern.

        Client
           |
           ↓
      Main Object
           |
           | delegates
           ↓
    Delegate Interface
           ▲
           |
     ┌─────┴─────┐
     │           │
Implementation A  Implementation B

```cpp
class Delegate {
public:
    virtual void execute() = 0;
    virtual ~Delegate() = default;
};

class ConcreteDelegate : public Delegate {
public:
    void execute() override {
        // actual work
    }
};

class MainObject {
private:
    Delegate* delegate_;

public:
    MainObject(Delegate* delegate)
        : delegate_(delegate) {}

    void doWork() {
        delegate_->execute();
    }
};
```

- The Delegator knows what should be done but the delegate knows
how this should be done.

DocumentEditor
       |
       | "save this document"
       ↓
StorageDelegate
       |
       ├── LocalStorage
       ├── CloudStorage
       └── NetworkStorage

| Delegation | Strategy |
|---|---|
| Transfer responsibility | Encapsulate interchangeable algorithm |
| "You do this for me" | "Choose how this is done" |
| Broad OO technique | Formal GoF behavioral pattern |
| Often uses composition | Uses composition |

- In practice, a delegate-based design can sometimes look almost identical to Strategy.

- Delegation is a design technique where an object transfers responsibility for an operation
to another object instead of implementing that operation itself. It is usually implemented 
through composition and polymorphism, allowing the delegate to be replaced independently of the delegating object.

- [Chromium Delegate Implementation](https://chatgpt.com/share/6a9016f5-4cdc-83e8-9d61-42e8ecb8ab8e)