# Command

-  It is a behavioral design pattern that turns a request into an object.
- It gives an ability to store, delay, queue, undo, log or execute requests 
independently of the object that actually performs the work.

### 4 Important participants

- Receiver
- Command
- Concrete Commands
- Invoker

Invoker ----|> Command 
               /\
                |
                |
                |
          Concrete Command ------|> Reciever

- For a small program, we should call the reciever directly.
- The Command Pattern becomes useful when we need to treat operations as first-class objects.

### Queue commands

Command 1
Command 2
Command 3
Command 4
       ↓
     Queue

Execute them later.

### Undo

execute()
   ↓
save command
   ↓
undo()

### Redo

Command
   ↓
history
   ↓
redo

### Logging

"User executed DeleteFileCommand"

### Scheduling

Execute command at 10:00 PM

### Macro commands

You can combine commands:
MacroCommand
   |
   +-- TurnOnLight
   +-- TurnOnFan
   +-- TurnOnTV

### Diagram
                +----------------+
                |    Invoker     |
                |                |
                | setCommand()   |
                | execute()      |
                +-------+--------+
                        |
                        | execute()
                        v
                +----------------+
                |    Command     |
                |                |
                | + execute()    |
                +-------+--------+
                        ^
                        |
             implements |
                        |
             +----------+----------+
             |                     |
             v                     v
    +----------------+    +----------------+
    | ConcreteCommand|    | ConcreteCommand|
    +-------+--------+    +-------+--------+
            |                     |
            |                     |
            v                     v
       +---------+           +---------+
       |Receiver |           |Receiver |
       +---------+           +---------+

Whenever we see a Command Pattern problem, ask:
Question 1
Who actually performs the operation?
→ Receiver
Question 2
What represents the request?
→ Command
Question 3
Who triggers the request?
→ Invoker
Question 4
What concrete class connects the request to the receiver?
→ Concrete Command

### Purpose
Command → encapsulates a request
Concrete Command → connects the request to a Receiver
Receiver → performs the actual work
Invoker → triggers the Command
Client → constructs/configures the objects