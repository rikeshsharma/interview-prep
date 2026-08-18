class AbstractClass {
  public:
  virtual AbstractClass* clone() = 0;
};

class ConcreteClass : public AbstractClass {
  public:
  AbstractClass* clone() override {
    // make new object, clones itself and return;
  }
};

class Client {
  public:
  void Application() {
    AbstractClass* object = new ConcreteClass();
    // does something
    AbstractClass * clone = object->clone();
    // does something more
  }

};