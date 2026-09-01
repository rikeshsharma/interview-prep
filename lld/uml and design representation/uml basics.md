# UML Basics

- Unified Modeling Language is a standardized visual language
used to represent software structure and behavior
- Relevant UML diagrams are:
  - Class diagram → structure of classes and relationships
  - Sequence diagram → how objects interact over time
  - State diagram → how an object changes states
  - Activity diagram → workflow/control flow

- Common UML Class Notations
  - A UML class is commonly represented as a box with three sections
                ┌─────────────────────────┐
                │         Car             │  ← Class name
                ├─────────────────────────┤
                │ - speed : int           │  ← Attributes
                │ - model : string        │
                ├─────────────────────────┤
                │ + start() : void        │  ← Methods
                │ + stop() : void         │
                └─────────────────────────┘

- UML Visibility
| UML | Meaning | C++ |
|---|---|---|
| `+` | Public | `public:` |
| `-` | Private | `private:` |
| `#` | Protected | `protected:` |
| `~` | Package/internal visibility | No direct C++ equivalent |

- A useful mnemonic:
  + = accessible, - = hidden, # = inherited access

- Other Common Class-Diagram Notations
  
  - Inheritance
      Animal
        ▲
        |
       Dog
  
  - Association : Customer is related to/knows about Order.
    Customer ───────── Order
  
  - Composition : strong ownership/lifetime relationship
    Car ◆──────── Engine
  
  - Aggregation : weaker "has-a" relationship
    Team ◇──────── Player
  
  - Dependency : A temporarily uses/depends on B
    A - - - > B

