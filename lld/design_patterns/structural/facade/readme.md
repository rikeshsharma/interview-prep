# Facade

- It is a structural design pattern that provides a simplified
interface to a library, a framework or a complex set of classes.

- A facade might provide limited functionality in comparison to working with the subsystem directly. 
However, it includes only those features that clients really care about.

- Use the Facade pattern when we need to have a limited but straightforward interface to a complex subsystem.

- Use the Facade when we want to structure a subsystem into layers.

- A Facade doesn't replace the subsystem classes.
- This is a common misunderstanding.
- The classes still exist:
                  Facade
                    |
        +-----------+-----------+
        |           |           |
        v           v           v
    Projector    Sound       Lights
                    |
                    v
                Streaming
- The Facade simply provides a simplified entry point.
- The underlying classes can still be used directly if necessary.

### When to use

- Situation 1 — Many classes are involved
- Situation 2 — There is a complicated sequence
- Situation 3 — You want to reduce coupling
