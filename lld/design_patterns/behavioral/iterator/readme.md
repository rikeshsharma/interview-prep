# Iterator

-  It is a behavioral design pattern that lets you traverse
all the elements of a collection without exposing its underlying 
representation (stack, list, tree, queue etc)
- used when there is a collection of data and traveral is necessary on it.
- when there is a collection of data, then every time we change the 
underlying data storage method, every time we need to update all of our
traversal. The client code needs to change everytime the collection internal changes
- Separate "how we store data" from "how we traverse data."

- when you require
  - I have a collection, but I don't want clients to know how it is stored or how traversal works.
