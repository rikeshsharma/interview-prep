# Interpreter

-  It is a behavioral design pattern used when we have a language 
or grammar consisting of expressions, and we want to 
interpret/evaluate those expressions.

- Convert a language's grammar into a set of classes, where each 
class knows how to interpret one part of the language.

### Participants

1. Abstract Expression
2. Terminal Expression
3. Non-Terminal Expression

```cpp
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};
```

### Context in Interpreter Pattern implementations

- A Context contains information required while interpreting.

```cpp
class Context {
    std::unordered_map<std::string, int> variables_;

public:
    void set(const std::string& name, int value) {
        variables_[name] = value;
    }

    int get(const std::string& name) {
        return variables_.at(name);
    }
};

int interpret(Context& context) {
    return context.get(name_);
}

virtual int interpret(Context& context) = 0; // more general interface
```

- Interpreter turns grammar rules into classes.



