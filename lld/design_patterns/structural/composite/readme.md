# Composite

- It is a structural design pattern, which lets us organise/compose
objects or components into tree like structure, and treat individual
objects and composition uniformly.

             Component
             /        \
           File       Folder
                       |
                 ---------------
                 |      |      |
                File   File   Folder
                              |
                             File

- Individual objects and groups of objects are treated uniformly 
through the same interface.

1. Component: One common interface
2. Leaf: An object that do not contain another Component
3. Composite: An object that contain other Component/Leaf

                    Component
                   /         \
                  /           \
               Leaf         Composite
                              |
                       children<Component>

- Composite is very closely related to tree recursion.
- When there is a heirarchical structure and both
  1. individual elements and
  2. group of elements
  support the same operation
then think of Composite design pattern.