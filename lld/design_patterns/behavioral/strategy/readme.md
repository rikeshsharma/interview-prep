# Strategy

- It is a behavioral design pattern that defines
a family of algorithms, put them each in seperate
class and make their object interchangable

- multiple ways of doing the same job
- want to switch the way of doing it without
changing the main class
- Put each algorithm/behavior into its own class, 
- then make the main class use one of those classes 
interchangeably.

### 3 Important components

1. Strategy Interface
2. Concrete Strategies
3. Context

### Relationship

1. Context HAS-A Strategy.
Example: 
- PaymentProcessor ─────HAS-A─────> PaymentStrategy

- CardPayment ──────────IS-A───────> PaymentStrategy
- UPIPayment ───────────IS-A───────> PaymentStrategy
- PayPalPayment ────────IS-A───────> PaymentStrategy

### When to choose strategy

1. Multiple algorithm to perform the same task.
2. There is a huge if/else or switch selecting algorithms.
3. You want to change behavior at runtime.
4. You want to add new algorithms without modifying the Context.