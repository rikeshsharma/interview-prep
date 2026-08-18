class ProductA {
  virtual void DoStuffA() = 0;
};

class ConcreteProductA1 : public ProductA {
  void DoStuffA() override {
    // concrete A1 does stuff
  }
};

class ConcreteProductA2 : public ProductA {
  void DoStuffA() override {
    // concrete A2 does stuff
  }
};

class ConcreteProductA3 : public ProductA {
  void DoStuffA() override {
    // concrete A3 does stuff
  }
};

class ProductB {
  virtual void DoStuffB() = 0;
};

class ConcreteProductB1 : public ProductB {
  void DoStuffB() override {
    // concrete B1 does stuff
  }
};

class ConcreteProductB2 : public ProductB {
  void DoStuffB() override {
    // concrete B2 does stuff
  }
};

class ConcreteProductB3 : public ProductB {
  void DoStuffB() override {
    // concrete B3 does stuff
  }
};

class ProductC {
  virtual void DoStuffC() = 0;
};


class ConcreteProductC1 : public ProductC {
  void DoStuffC() override {
    // concrete C1 does stuff
  }
};

class ConcreteProductC2 : public ProductC {
  void DoStuffC() override {
    // concrete C2 does stuff
  }
};

class ConcreteProductC3 : public ProductC {
  void DoStuffC() override {
    // concrete C3 does stuff
  }
};

class AbstractFactory {
  public:
  virtual void CreateProductA() = 0;
  virtual void CreateProductB() = 0;
  virtual void CreateProductC() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
  public:
  void CreateProductA() override {
    // creates A1
  }
  void CreateProductB() override {
    // creates B1
  }
  void CreateProductC() override {
    // creates C1
  }
};

class ConcreteFactory2 : public AbstractFactory {
  public:
  void CreateProductA() override {
    // creates A2
  }
  void CreateProductB() override {
    // creates B2
  }
  void CreateProductC() override {
    // creates C2
  }
};

class ConcreteFactory3 : public AbstractFactory {
  public:
  void CreateProductA() override {
    // creates A3
  }
  void CreateProductB() override {
    // creates B3
  }
  void CreateProductC() override {
    // creates C3
  }
};

class Client {
  void Application() {
    AbstractFactory* factory = new ConcreteFactory1();
    factory->CreateProductA();
    factory->CreateProductB();
    factory->CreateProductC();
  }
};