# Visitor

- It is a behavioral design pattern that seperates
algorithms from the object on which they operate.

- It is used when we have a stable set of object types,
but you frequently want to add new operations to those objects.

- The key idea is to separate an operation from the
objects on which that operation operates.

             Visitor
                │
       ┌────────┼────────┐
       ↓        ↓        ↓
   visit(Pdf) visit(Word) visit(Excel)


             Documents
                │
       ┌────────┼────────┐
       ↓        ↓        ↓
      PDF     Word      Excel

### Important Components

```cpp
class DocumentVisitor {
public:
    virtual void visit(PdfDocument&) = 0;
    virtual void visit(WordDocument&) = 0;
    virtual void visit(ExcelDocument&) = 0;
};

class PrintVisitor : public DocumentVisitor {
public:
    void visit(PdfDocument&) override;
    void visit(WordDocument&) override;
    void visit(ExcelDocument&) override;
};

class SizeVisitor : public DocumentVisitor {
public:
    void visit(PdfDocument&) override;
    void visit(WordDocument&) override;
    void visit(ExcelDocument&) override;
};
```
### The Important Part: accept()
Each element has:
```cpp
  virtual void accept(DocumentVisitor&) = 0;
```
For example:
```cpp
class PdfDocument : public Document {
public:
    void accept(DocumentVisitor& visitor) override {
        visitor.visit(*this);
    }
};
```
Notice:
visitor.visit(*this);
Because this is a PdfDocument*, *this is a PdfDocument&.
Therefore this selects:
visit(PdfDocument&)
Similarly:
```cpp
class WordDocument : public Document {
public:
    void accept(DocumentVisitor& visitor) override {
        visitor.visit(*this);
    }
};
```

### Why Not Just Call visitor.visit(document)?
Suppose you have:
Document* document = new PdfDocument();
The static type is:
Document*
but the actual object is:
PdfDocument
If the visitor only had:
visit(Document&)
you wouldn't get the type-specific behavior you want.

### Double Dispatch

- Because C++ chooses overloaded functions using the static (compile-time)
types of the arguments, not their runtime types.
```cpp
void collide(Car&, Car&);
void collide(Car&, Truck&);
void collide(Truck&, Car&);
void collide(Truck&, Truck&);

for above if we call

Vehicle& a = car;
Vehicle& b = truck;
collide(a, b);
```
- None of those four functions will be called. The code will fail to compile.
- because
a → Vehicle&
b → Vehicle&
 so compiler essentially ask
Which collide(Vehicle&, Vehicle&) exists?
- None

### This is especially important for the Visitor Pattern

This is actually the reason the Visitor Pattern exists.
Suppose:
```cpp
class Shape {
public:
    virtual void accept(Visitor&) = 0;
};

class Circle : public Shape {
public:
    void accept(Visitor& v) override {
        v.visit(*this);
    }
};
```
Then:
```cpp
Shape* shape = new Circle();
shape->accept(visitor);
```
First dispatch
C++ uses the runtime type of shape:
shape
  ↓
Circle
  ↓
Circle::accept()

That's single dispatch.

Then inside Circle::accept():
```cpp
v.visit(*this);
```
Because *this is statically known to be a Circle, the appropriate overload:
visit(Circle&)
is selected.

### Structure

1. Element
2. Concrete Element
3. Visitor
4. Concrete Visitor

### Mental Model

Without Visitor
The document says:
"I know how to print myself."

With Visitor
The document says:
"I know how to let someone operate on me."
The visitor says:
"I know what to do with each type."

### When to use visitor

1. Object structure is stable
2. But Operation keeps on increasing

### Downside

Visitor has an important downside.
Suppose you have:
Pdf
Word
Excel
and then introduce:
PowerPoint
You now have to modify the visitor interface:
virtual void visit(PowerPoint&) = 0;
And every concrete visitor must implement it.

| Change | Visitor |
|---|---|
| Add new operation | ✅ Easy |
| Add new element type | ❌ Expensive |
| Many operations | ✅ Excellent |
| Stable object hierarchy | ✅ Excellent |