class AbstractProduct {
  virtual void DoStuff() = 0;
};

class ConcreteProductA : public AbstractProduct {
  void DoStuff() override {
    // some stuff done by A
  }
};

class ConcreteProductB : public AbstractProduct {
  void DoStuff() override {
    // some stuff done by B
  }
};

class AbstractCreator {
  public:
  virtual AbstractProduct CreateProduct() = 0;
};

class ConcreteCreatorA : public AbstractCreator {
  public:
  AbstractProduct CreateProduct() override {
    // return new ConcreteProductA;
  }
};

class ConcreteCreatorB : public AbstractCreator {
  public:
  AbstractProduct CreateProduct() override {
    // return new ConcreteProductB;
  }
};

class User {
  void CreateAndUse() {
    AbstractCreator * creator = new ConcreteCreatorA;
    creator->CreateProduct();
  }
};