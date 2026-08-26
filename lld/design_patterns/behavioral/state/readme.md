# State

- It is a behavioral design pattern that lets an object
alter its behaviour when its internal state changes.
- The State pattern is closely related to the concept 
of a Finite-State Machine.
- switching rules, called transitions, are also finite and predetermined.

- The State pattern suggests that we create new classes for all possible 
states of an object and extract all state-specific behaviors into these classes.

### For simpler state related objects
```cpp
#include <iostream>

class VendingMachine {
public:

    enum class State {
        NoMoney,
        MoneyInserted,
        Dispensing
    };

private:
    State state_ = State::NoMoney;

public:

    void insertMoney() {

        switch (state_) {

        case State::NoMoney:
            std::cout << "Money inserted\n";
            state_ = State::MoneyInserted;
            break;

        case State::MoneyInserted:
            std::cout << "Money already inserted\n";
            break;

        case State::Dispensing:
            std::cout << "Cannot insert money while dispensing\n";
            break;
        }
    }

    void selectItem() {

        switch (state_) {

        case State::NoMoney:
            std::cout << "Insert money first\n";
            break;

        case State::MoneyInserted:
            std::cout << "Item selected. Dispensing...\n";
            state_ = State::Dispensing;
            break;

        case State::Dispensing:
            std::cout << "Already dispensing\n";
            break;
        }
    }

    void dispenseComplete() {

        switch (state_) {

        case State::NoMoney:
            std::cout << "Nothing to dispense\n";
            break;

        case State::MoneyInserted:
            std::cout << "Item has not been selected\n";
            break;

        case State::Dispensing:
            std::cout << "Dispensing complete\n";
            state_ = State::NoMoney;
            break;
        }
    }
};
```

- Now if we add 
1. NoMoney
2. MoneyInserted
3. ItemSelected
4. Dispensing
5. OutOfStock
6. Maintenance
7. Refunding
8. Error
9. Locked
... so on

- Each of these method will require a gaint switch also
- deeper problem is that state-specific behavior is scattered throughout the Context class.
- so the behavior of each state should ideally live together.
  - The behavior for NoMoney should ideally live together.
  - The behavior for MoneyInserted should live together.
  - The behavior for Dispensing should live together.

State Pattern says:
- Represent each state as an object and move state-specific behavior into that object.

- Instead of 

VendingMachine
    |
    └── switch(state)

we have

                 ┌── NoMoneyState
                 │
VendingMachine ──┼── MoneyInsertedState
                 │
                 └── DispensingState

### 3 Important Pieces

1. Context: object whose behavior changes
2. State Interface: define the interface that the state object must implement
3. Concrete State: Each class contains the behavior appropriate for that state.

### State Transition

- The state needs to access context because after performing the particular 
state related operation, it needs the context to transition itself to another state.

### Structure

                    ┌─────────────────────┐
                    │       Context       │
                    │   VendingMachine    │
                    ├─────────────────────┤
                    │ State* currentState │
                    ├─────────────────────┤
                    │ insertMoney()       │
                    │ selectItem()        │<---------+
                    │ cancel()            |          |
                    | setState()          │          |
                    └──────────┬──────────┘          |
                               │                     |
                               │ delegates           |
                               ↓                     | setState()
                    ┌─────────────────────┐          |
                    │       State         │          |
                    │    <<interface>>    │          |
                    ├─────────────────────┤          |
                    | Context* context.   |          |
                    ├──────────────────── |          |
                    │ insertMoney()       │          |
                    │ selectItem()        │----------+
                    │ cancel()            │
                    └──────────┬──────────┘
                               │
              ┌────────────────┼────────────────┐
              ↓                ↓                ↓
       NoMoneyState     MoneyInsertedState  DispensingState

