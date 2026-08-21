class Singleton {
private:
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }
};

// Thread-safe initialization — since C++11, initialization 
// of a function-local static is guaranteed to be thread-safe.