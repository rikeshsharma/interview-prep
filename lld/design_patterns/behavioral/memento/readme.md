# Memento

- It s a behavioral design pattern that lets you save and restore the
previous state of an object without revealing the details of its implementation.

Memento = Take a snapshot now, restore that snapshot later.

Memento: It is an object that store the snapshot of another object's state

### 3 Main Participants

1. Originator: The object whose state we want to save
  - it knows what state mean
  - how to create a snapshot
  - how to restore a snapshot
2. Memento: The object that has and saves the state of originator
  - It contain the state of the originator
3. Caretaker: Manages the snapshots or state or memento of originator
  - It asks the originator for the memento
  - stores it
  - later gives it back to the originator for restoration

Here it is in mermaid:The source, if you want to drop it into a README or docs site:

                         creates
        +------------------------------>
        |                               |
+-------------------+          +-------------------+
|    Originator     |          |      Memento      |
+-------------------+          +-------------------+
| - state: State    |          | - state: State    |
+-------------------+          +-------------------+
| + save(): Memento |          | + getState():State|
| + restore(m:      |          | + Memento(s:State)|
|   Memento)        |          +-------------------+
+-------------------+               ^    ^
        ^    |         restore      |    |
        |    +----------------------+    |
        | requests                       | stores
        |                                |
        |                                |
        |         +-------------------+  |
        |         |     Caretaker     |  |
        |         +-------------------+  |
        +---------| - history:        |--+
                  |   List<Memento>   |
                  +-------------------+
                  | + undo()          |
                  +-------------------+

### Use Memento when:

- an object has complicated internal state
- you need Undo/Redo
- you need rollback
- you need checkpoints
- you don't want to expose internal state
- another object should manage history without understanding the state
