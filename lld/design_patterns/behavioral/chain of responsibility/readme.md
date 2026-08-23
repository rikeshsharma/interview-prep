# Chain of Responsibility

-  It is a behavioral design pattern that allows to pass a
request along a chain of handlers, upon recieving the request
the handler can decide to process the request or pass it to the
next handler in chain.

Handler interface <---- used by Client
  execute() = 0;
      |
      |
Concrete Handler
  Handler* next;
  execute()
