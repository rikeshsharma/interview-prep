/*
Problem: Document Editor with Undo
You are building a document editor.
The editor has the following state:
content
cursorPosition
fontSize
For example:
content = "Hello World"
cursorPosition = 5
fontSize = 16
The editor must support saving and restoring its complete state.
Requirements
Implement these classes:
class DocumentMemento;
class DocumentEditor;
class EditorHistory;
DocumentEditor
It must maintain:
std::string content;
int cursorPosition;
int fontSize;
Provide:
void setContent(const std::string& content);
void setCursorPosition(int position);
void setFontSize(int size);

void appendText(const std::string& text);

void display() const;

DocumentMemento save() const;
void restore(const DocumentMemento& memento);
appendText() should append the supplied text to the current content.
DocumentMemento
This class must represent a snapshot of the complete editor state:
content
cursorPosition
fontSize
The important requirement is:
EditorHistory must not directly access the internal state of DocumentMemento.

Only DocumentEditor should know how to create and restore the actual editor state.
You may use friend class DocumentEditor if you think it is appropriate.
EditorHistory
This is the Caretaker.
It should maintain a history of saved states.
Provide:
void save(const DocumentEditor& editor);

bool undo(DocumentEditor& editor);
Behavior:
save()
Save the current state of the editor.
undo()
- If there is no previous saved state, return false.
- Otherwise restore the most recently saved state.
- Remove that state from history.
- Return true.
Important Scenario
The provided main() will perform operations roughly like this:
Editor initially:
content = "Hello"
cursor = 5
fontSize = 12

save()

Modify editor:
content = "Hello World"
cursor = 11
fontSize = 16

save()

Modify editor again:
content = "Hello World!"
cursor = 12
fontSize = 20

undo()

display()

undo()

display()

undo()
The expected states after the two successful undos are:
First display:

content = "Hello World"
cursor = 11
fontSize = 16

Second display:

content = "Hello"
cursor = 5
fontSize = 12
The third undo() should return:
false
because there are no more saved states.
Constraints
You only implement:
DocumentMemento
DocumentEditor
EditorHistory
Do not modify main().
Use standard C++ only.
You may use:
*/

#include <iostream>
#include <string>
#include <vector>
/*
and any standard-library container you genuinely need.
One important design requirement
Don't solve this by making all DocumentMemento fields public.
The challenge is specifically testing whether you understand the encapsulation aspect of Memento:
DocumentEditor
↕
Memento
↑
|
EditorHistory
(stores it,
doesn't inspect it)
Provided main()
I have checked the types and the calls in this main() so your implementation should be designed to compile against it:
*/

class DocumentEditor;

class DocumentMemento {
  std::string content_;
  int cursorPosition_;
  int fontSize_;
public:
  DocumentMemento(const std::string& content, int position, int size)
                  : content_(content), cursorPosition_(position), fontSize_(size){}

  friend class DocumentEditor;
};

class DocumentEditor {
  std::string content_;
  int cursorPosition_;
  int fontSize_;
public:
  void setContent(const std::string& content) {
    content_ = content;
  }
  void setCursorPosition(int position) {
    cursorPosition_ = position;
  }
  void setFontSize(int size) {
    fontSize_ = size;
  }

  void appendText(const std::string& text) {
    content_=content_+text;
  }

  void display() const {
    std::cout << content_ << "\n";
  }
  DocumentMemento save() const {
    return DocumentMemento(content_, cursorPosition_, fontSize_);
  }
  void restore(const DocumentMemento& memento) {
    content_ = memento.content_;
    cursorPosition_ = memento.cursorPosition_;
    fontSize_ = memento.fontSize_;
  }
};

class EditorHistory {
  std::vector<DocumentMemento> history_;
public:
  void save(const DocumentEditor& editor) {
    history_.push_back(editor.save());
  }
  bool undo(DocumentEditor& editor) {
    if(history_.size() > 0) {
      editor.restore(history_.back());  
      history_.pop_back();
      return true;
    }
    return false;
  }
};

int main() {
    DocumentEditor editor;
    EditorHistory history;

    editor.setContent("Hello");
    editor.setCursorPosition(5);
    editor.setFontSize(12);

    history.save(editor);

    editor.appendText(" World");
    editor.setCursorPosition(11);
    editor.setFontSize(16);

    history.save(editor);

    editor.appendText("!");
    editor.setCursorPosition(12);
    editor.setFontSize(20);

    history.undo(editor);

    editor.display();

    history.undo(editor);

    editor.display();

    bool result = history.undo(editor);

    std::cout << "Third undo successful: "
              << std::boolalpha
              << result
              << std::endl;

    return 0;
}
//Your task: implement the three classes so this main() works correctly.
