# Bridge

- Bridge is a structural design pattern that lets you split a large class
or a set of closely related classes into two separate hierarchies.

abstraction -> is a high-level control layer for some entity. 
              (do not confuse with abstract class)
and implementation -> the part where actual work is done. 
                      (do not confuse with concrete class)

which can be developed independently of each other.

- Separate two dimensions that can change independently.

Abstraction
     |
     | HAS-A
     ↓
Implementation

So Bridge combines:
1. inheritance for each independent dimension
2. composition to connect those dimensions
                    ┌──────────────┐
                    │    Client    │
                    └──────┬───────┘
                           │
                           │ uses
                           ▼
              ┌─────────────────────────┐
              │      Abstraction        │
              │─────────────────────────│
              │ - implementation        │──────────────┐
              │                         │              │
              │ + feature1()            │              │
              │ + feature2()            │              │
              └────────────┬────────────┘              │
                           ▲                           │
                           │                           │
                    ┌──────┴────────────┐              │
                    │ Refined           │              │
                    │ Abstraction       │              │
                    │───────────────────│              │
                    │ + featureN()      │              │
                    └───────────────────┘              │
                                                       │
                                                       │
                                                       ▼
                                         ┌────────────────────────┐
                                         │     Implementation     │
                                         │       «interface»      │
                                         │────────────────────────│
                                         │ + method1()            │
                                         │ + method2()            │
                                         │ + method3()            │
                                         └───────────▲────────────┘
                                                     │
                                                     │ implements
                                                     │
                                      ┌──────────────┴──────────────┐
                                      │   Concrete Implementations │
                                      │                            │
                                      │ + method1()                │
                                      │ + method2()                │
                                      │ + method3()                │
                                      └────────────────────────────┘


Abstraction ───────────────► Implementation
              composition



        Abstraction hierarchy          Implementation hierarchy

        Abstraction                    Implementation
             ▲                              ▲
             │                              │
             │                              │
     RefinedAbstraction             ConcreteImplementation1
                                           ConcreteImplementation2
                                           ConcreteImplementation3