# Design Principles

## Solid Design Principle

- Principles for designing good code.
- Tells us how our code should be structured.
- Easier to understand, change, extend and test.
- Flexibility, Reuse, Efficient

1. **Single Responsibility Principle**:
   A class should have one primary resposnisibilty and therefore one reason to change.

2. **Open Close Principle**:
   Software entities should be open for extension but closed for modification.
   We should be able to add new behavior without constantly modifying existing tested code.

3. **Liskov Substitution Principle**:
   Object of a subclass should be replaceable with object of a superclass without breaking 
   the correctness of the program.
   If B is a subtype of A, wherever A is expected, B should work correctly.
   LSP = If B inherits from A, then code that works with an A should continue to work correctly when given a B.

4. **Interface Segragation Principle**:
   Clients should not be forced to depend on interfaces they do not use.
   Don't create giant interfaces. Create smaller, focused interfaces.

5. **Dependency Inversion Principle**:
   High-level modules should not depend directly on low-level modules. Both should depend on abstractions. and
   Abstractions should not depend on details. Details should depend on abstractions.

## Design Patterns

- Common blueprints to usually occuring problems in software design, they are not algorithms.
- They are pre-made blueprints that can be customised to solve design problem in code.

**Note**: SOLID tells us how the code should be structured whereas the Desing Pattern gives us
a proven structure that we can use.

1. Creational Design Pattern
2. Structural Design Pattern
3. Behavioural Design Pattern
