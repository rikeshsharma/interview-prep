/*
Problem: Document Processing System
You are building a document processing framework.
Your system supports different document types:
- PDFDocument
- WordDocument
- TextDocument
Every document must follow this exact processing pipeline:
1. Open document
2. Read document data
3. Validate document
4. Process document
5. Save document
6. Close document
The order must never change.
However, the implementation of some steps differs depending on the document type.
Common behavior
For every document:
- openDocument() prints:
Opening document...
- closeDocument() prints:
Closing document...
- saveDocument() prints:
Saving document...
Variable behavior
Each document must implement:
PDFDocument
Read → Reading PDF binary data...
Validate → Validating PDF structure...
Process → Processing PDF pages...
WordDocument
Read → Reading DOCX content...
Validate → Validating Word document structure...
Process → Processing Word paragraphs...
TextDocument
Read → Reading plain text...
Validate → Validating text encoding...
Process → Processing text lines...
Additional requirement: validation failure
There is one more twist.
validateDocument() should return a bool.
If validation fails, the pipeline must stop immediately.
So the algorithm should conceptually be:
open
  ↓
read
  ↓
validate
  ↓
if validation failed → close → STOP
  ↓
process
  ↓
save
  ↓
close
The base class should own this entire algorithm.
For this exercise, make:
- PDFDocument::validateDocument() → true
- WordDocument::validateDocument() → true
- TextDocument::validateDocument() → false
Therefore, TextDocument should produce:
Opening document...
Reading plain text...
Validating text encoding...
Closing document...
It must not print:
Processing text lines...
Saving document...
Your task
Implement only the Template Method design-pattern-related classes.
You need to create:
class DocumentProcessor
and:
class PDFDocument
class WordDocument
class TextDocument
Constraints
1. DocumentProcessor must contain the Template Method.
2. The Template Method must control the exact processing order.
3. Common operations should be implemented in the base class.
4. Variable operations should be implemented by derived classes.
5. Use runtime polymorphism.
6. validateDocument() must determine whether processing continues.
7. Do not duplicate the overall algorithm in derived classes.
8. Use proper override.
9. You may make appropriate methods protected.
10. The Template Method itself should not be overridden by derived classes.
I will provide main()
So do not write main().
Your code will be tested approximately like this:
*/
#include <iostream>
#include <string>

class DocumentProcessor {
public:

  void OpenDocument() const {
    std::cout << "Opening document...\n";
  }

  virtual void ReadDocument() const = 0;
  virtual bool ValidateDocument() const = 0;
  virtual void ProcessDocumentContent() const = 0;

  void SaveDocument() const {
    std::cout << "Saving document...\n";
  }
  void CloseDocument() const {
    std::cout << "Closing document...\n";
  }

  void ProcessDocument() const {
    OpenDocument();
    ReadDocument();

    if(ValidateDocument()){
      ProcessDocumentContent();
      SaveDocument();
    }

    CloseDocument();
  }
  virtual ~DocumentProcessor() = default;
};

class PDFDocument : public DocumentProcessor {
public:
  void ReadDocument() const override {
    std::cout << "Reading PDF binary data...\n";
  }
  bool ValidateDocument() const override {
    std::cout << "Validating PDF structure...\n";
    return true;
  }
  void ProcessDocumentContent() const override {
    std::cout << "Processing PDF pages...\n";
  }
};

class WordDocument : public DocumentProcessor {
public:
  void ReadDocument() const override {
    std::cout << "Reading DOCX content...\n";
  }
  bool ValidateDocument() const override {
    std::cout << "Validating Word document structure...\n";
    return true;
  }
  void ProcessDocumentContent() const override {
    std::cout << "Processing Word paragraphs...\n";
  }
};

class TextDocument : public DocumentProcessor {
public:
  void ReadDocument() const override {
    std::cout << "Reading plain text...\n";
  }
  bool ValidateDocument() const override {
    std::cout << "Validating text encoding...\n";
    return false;
  }
  void ProcessDocumentContent() const override {
    std::cout << "Processing text lines...\n";
  }
};

int main() {
    PDFDocument pdf;
    WordDocument word;
    TextDocument text;

    DocumentProcessor* documents[] = {
        &pdf,
        &word,
        &text
    };

    for (DocumentProcessor* document : documents) {
        document->ProcessDocument();
        std::cout << "----------------\n";
    }

    return 0;
}
/*
Your job is to implement everything necessary for this main() to compile and behave correctly.
Don't look for a solution yet. Try designing the base class first. The key question to ask yourself is:
"Which method should contain the fixed algorithm, and which methods should be virtual?"
*/