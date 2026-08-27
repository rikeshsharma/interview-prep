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
   1. Factory Method
   2. Abstract Factory
   3. Builder
   4. Singleton
   5. Prototype
2. Structural Design Pattern
   1. Adapter
   2. Bridge
   3. Composite
   4. Decorator
   5. Facade
   6. Flyweight
   7. Proxy
3. Behavioural Design Pattern
   1. Chain of Responsibility
   2. Command
   3. Iterator
   4. Mediator
   5. Memento
   6. Observer
   7. State
   8. Strategy
   9. Template Method
   10. Visitor
   11. Interpreter

## Complete Low-Level Design (LLD) Learning Roadmap

The topics below are ordered from foundational concepts to advanced LLD design and interview-level practice.

| Sequence | Topic Title | All Things Included in This Topic That Need to Be Learned | Importance Score (10) | Priority Score (10) | Interview Importance (10) |
|---:|---|---|---:|---:|---:|
| 1 | Advanced OOP & C++ Design | Composition vs inheritance; Interfaces / abstract classes; Dependency Injection; Immutability; RAII & ownership; Smart pointers; Move semantics; Rule of 5 | 10 | 10 | 10 |
| 2 | Design Principles Beyond SOLID | DRY; KISS; YAGNI; Law of Demeter; GRASP principles; Cohesion & coupling | 9 | 9 | 9 |
| 3 | UML & Design Representation | Class diagrams; Sequence diagrams; State diagrams; Activity diagrams; Object relationships | 8 | 8 | 8 |
| 4 | Domain Modeling | Identify entities; Value objects; Aggregates; Define invariants and business rules; Model domain relationships correctly; State machines / lifecycle modeling | 9 | 9 | 9 |
| 5 | LLD Modeling & Problem-Solving | Requirements → Use cases → Classes → Relationships → Interfaces → Interactions → Code; requirement analysis; identifying responsibilities; choosing abstractions; modeling object interactions | 10 | 10 | 10 |
| 6 | API & Interface Design | Public vs private interfaces; Contracts; Preconditions; Postconditions; Versioning; Backward compatibility | 8 | 8 | 8 |
| 7 | Error & Exception Handling | Exception safety; Error propagation; Failure handling strategies; Designing predictable failure behavior | 8 | 7 | 7 |
| 8 | Memory & Resource Management | Ownership models; Lifetime management; Resource leaks; RAII in depth; resource ownership boundaries | 10 | 9 | 9 |
| 9 | Testing & Maintainability | Unit testing; Mocking; Dependency injection for testing; Interface-based design; Testable architecture | 9 | 8 | 8 |
| 10 | Refactoring & Code Review | Identify bad designs; Refactor legacy code; Detect code smells; Improve extensibility/testability; Know when NOT to use a design pattern | 9 | 8 | 9 |
| 11 | Event-Driven Design | Observer/event systems; Event bus; Callbacks; Pub/Sub concepts; Decoupled event handling | 8 | 7 | 7 |
| 12 | Serialization & Persistence | Object serialization; File/database interaction; Repository pattern; DTOs; Persistence boundaries | 7 | 6 | 6 |
| 13 | Architectural Patterns | MVC; MVP / MVVM; Layered architecture; Hexagonal / Ports & Adapters; Clean Architecture | 8 | 6 | 7 |
| 14 | Concurrency & Thread-Safe Design | Mutexes / locks; Condition variables; Thread pools; Producer-consumer; Race conditions; Deadlocks; Thread-safe classes | 9 | 8 | 8 |
| 15 | Performance-Oriented LLD | Caching; Object pooling; Lazy initialization; Copy vs move; Allocation/performance trade-offs | 8 | 7 | 8 |
| 16 | Security-Oriented Design | Authentication/authorization boundaries; Input validation; Secure resource handling | 7 | 5 | 6 |
| 17 | Complete LLD Problem Practice | Parking Lot; Vending Machine; Library Management; Elevator; ATM; Chess; Splitwise; Cab Booking; Notification System; Logging Framework; Cache; Rate Limiter; progressively harder end-to-end designs | 10 | 10 | 10 |

### Recommended Practice Strategy

After learning the foundational topics, repeatedly cycle through:

**Requirements → Domain Model → UML → Class Design → SOLID → Design Patterns → API Design → Error Handling → Implementation → Tests → Refactoring → Performance/Concurrency considerations**

### Prompt

1. Teach me <Name> Design Pattern in Simple but Complete manner.
At last give me a code question to implement just <Name> design pattern
that is difficult enough to challenge me but also easy enough to be completed.
Please write the int main code by yourself only, I only need to implement the
design pattern related codes. Make sure you rechecked for the type mismatch in 
the generated question.
2. Go on increasing difficulty level in subsequent questions.
