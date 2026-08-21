# Adapter

- also known as wrapper
- it is a structural design pattern which enables object of incompatible
interfaces to communicate/collaborate.

1. The adapter gets an interface, compatible with one of the existing objects.
2. Using this interface, the existing object can safely call the adapter’s methods.
3. Upon receiving a call, the adapter passes the request to the second object, 
but in a format and order that the second object expects.

## Types

1. Object Adapter: The Adapter contains the adaptee.
2. Class Adapter: The Adapter inherits from the adaptee as well.
