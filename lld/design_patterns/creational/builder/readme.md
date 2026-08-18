# Builder

- It is a creational design pattern that lets us create complex object step by step
- Suppose there a very complex object needs to be created, if we directly pass
all the information required to create it, that will be very monstorous and 
complicated function. Better will be if we use setter in class of that object,
this will make the class monstorous and also violate SRP so we create a interface
builder and implements for different concrete class of our complex classes, and either
1. add setters in builder or
2. add setters that returns product type
so that object can be made cascadingly.
