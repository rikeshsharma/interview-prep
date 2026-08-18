class Singleton {
  Singleton(){}
  Singleton(const Singleton& object){}
  Singleton(Singleton&& object){}
  static Singleton* instance_;
  public:
  static Singleton* GetInstance(){
    if(instance_) return instance_;
    instance_ = new Singleton();
    return instance_;
  }
};
Singleton* Singleton::instance_ = nullptr;
