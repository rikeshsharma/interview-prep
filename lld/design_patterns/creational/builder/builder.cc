class HTMLElement {
  public:
  virtual void TagName() = 0;
  virtual void ClassName() = 0;
  virtual void Id() = 0;
  virtual void Property() = 0;
  virtual void InnerText() = 0;
  virtual void InnerChild() = 0;
};

class Paragraph : public HTMLElement {
  public:
   void TagName() override {
    // p
   }
   void ClassName() override {
    // some class name
   }
   void Id() override {
    // some id
   }
   void Property() override {
    // style, other
   }
   void InnerChild() override {
    // Inner child some html element or null
   }
   void InnerText() override {
    // empty or some text
   }
};

class Div : public HTMLElement {
  public:
   void TagName() override {
    // div
   }
   void ClassName() override {
    // some class name
   }
   void Id() override {
    // some id
   }
   void Property() override {
    // style, other
   }
   void InnerChild() override {
    // Inner child some html element or null
   }
   void InnerText() override {
    // empty or some text
   }
};


class Span : public HTMLElement {
  public:
   void TagName() override {
    // span
   }
   void ClassName() override {
    // some class name
   }
   void Id() override {
    // some id
   }
   void Property() override {
    // style, other
   }
   void InnerChild() override {
    // Inner child some html element or null
   }
   void InnerText() override {
    // empty or some text
   }
};


class HTMLElementBuilder {
  public:
  virtual HTMLElementBuilder* SetTagName() = 0;
  virtual HTMLElementBuilder* SetClassName() = 0;
  virtual HTMLElementBuilder* SetId() = 0;
  virtual HTMLElementBuilder* SetProperty() = 0;
  virtual HTMLElementBuilder* SetInnerText() = 0;
  virtual HTMLElementBuilder* SetInnerChild() = 0;
};

class ParagraphBuilder : public HTMLElementBuilder {
  public:
  HTMLElementBuilder* SetTagName() override {
    // set and return
  }
  HTMLElementBuilder* SetClassName() override {
    // set and return
  }
  HTMLElementBuilder* SetId() override {
    // set and return
  }
  HTMLElementBuilder* SetProperty() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerChild() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerText() override {
    // set and return
  }
};

class DivBuilder : public HTMLElementBuilder {
  public:
  HTMLElementBuilder* SetTagName() override {
    // set and return
  }
  HTMLElementBuilder* SetClassName() override {
    // set and return
  }
  HTMLElementBuilder* SetId() override {
    // set and return
  }
  HTMLElementBuilder* SetProperty() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerChild() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerText() override {
    // set and return
  }
};

class SpanBuilder : public HTMLElementBuilder {
  public:
  HTMLElementBuilder* SetTagName() override {
    // set and return
  }
  HTMLElementBuilder* SetClassName() override {
    // set and return
  }
  HTMLElementBuilder* SetId() override {
    // set and return
  }
  HTMLElementBuilder* SetProperty() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerChild() override {
    // set and return
  }
  HTMLElementBuilder* SetInnerText() override {
    // set and return
  }
};

class Client {

  void Application() {
    HTMLElementBuilder * builder = new DivBuilder();
    builder->SetClassName()->SetId()->SetInnerText();
  }
};