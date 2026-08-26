/*
Your task is to implement:
- Observer
- Subject
- StockMarket
- MobileApp
- TradingTerminal
- StockLogger
The scenario is:
A StockMarket maintains a stock price. Multiple applications can subscribe to it. 
Whenever the price changes, all subscribed observers must be notified.

Requirements
1. Observer must be an abstract interface.
2. It must have an update() function that receives the stock symbol and new price.
3. Subject must provide:
   - attach()
   - detach()
   - notify()
4. StockMarket must:
   - maintain observers
   - maintain stock symbol
   - maintain current price
   - notify observers whenever the price changes
5. MobileApp should print:
MobileApp: AAPL price changed to 195.5
6. TradingTerminal should print:
TradingTerminal: AAPL = 195.5
7. StockLogger should print:
StockLogger: Recorded AAPL at 195.5
8. detach() must actually stop an observer from receiving future notifications.
9. Do not use dynamic_cast.
10. Use the Observer pattern rather than hard-coding concrete observer types inside StockMarket.
Important type requirement
Use:
double price
for the stock price everywhere it represents a price. This avoids an accidental int/double mismatch.
Starter Code
Implement everything marked TODO.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ============================================================
// TODO 1: Implement Observer
// ============================================================

class Observer {
public:
  virtual void update(const std::string& symbol, double price) = 0;
  virtual ~Observer() = default;
};


// ============================================================
// TODO 2: Implement Subject
// ============================================================

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};


// ============================================================
// TODO 3: Implement StockMarket
// ============================================================

class StockMarket : public Subject {
private:
    std::string symbol_;
    double price_;
    std::vector<Observer*> observer_list_;

public:
    StockMarket(const std::string& symbol, double initial_price) 
                : symbol_(symbol), price_(initial_price) {}

    void setPrice(double price) {
      if(price < 0) return;
      price_ = price;
      notify();
    }

    void attach(Observer* observer) override {
      if(observer == nullptr) return;
      for(auto obs: observer_list_) {
        if(obs == observer) {
          return;
        }
      }

      observer_list_.push_back(observer);
    }

    void detach(Observer* observer) override {
      if(observer == nullptr) return;
      for(int i = 0; i<observer_list_.size(); i++) {
        if(observer_list_[i] == observer) {
          observer_list_.erase(observer_list_.begin() + i);
          return;
        }
      }
    }

    void notify() override {
      for(auto observer: observer_list_) {
        observer->update(symbol_, price_);
      }
    }
};

// ============================================================
// TODO 4: Implement MobileApp
// ============================================================

class MobileApp : public Observer {
public:
    void update(const std::string& symbol, double price) override {
      std::cout << "MobileApp: "<<symbol<<" price changed to "<<price << std::endl;
    }
};


// ============================================================
// TODO 5: Implement TradingTerminal
// ============================================================

class TradingTerminal : public Observer {
public:
    void update(const std::string& symbol, double price) override {
      std::cout << "TradingTerminal: "<<symbol<<" = "<<price<< std::endl;
    }
};


// ============================================================
// TODO 6: Implement StockLogger
// ============================================================

class StockLogger : public Observer {
public:
  void update(const std::string& symbol, double price) override {
    std::cout << "StockLogger: Recorded "<<symbol<<" at "<<price<< std::endl;
  }
};


// ============================================================
// MAIN — DO NOT MODIFY
// ============================================================

int main() {
    StockMarket market("AAPL", 190.0);

    MobileApp mobile;
    TradingTerminal terminal;
    StockLogger logger;

    market.attach(&mobile);
    market.attach(&terminal);
    market.attach(&logger);

    std::cout << "--- First update ---\n";
    market.setPrice(195.5);

    std::cout << "\n--- Removing terminal ---\n";
    market.detach(&terminal);

    std::cout << "--- Second update ---\n";
    market.setPrice(198.25);

    std::cout << "\n--- Removing logger ---\n";
    market.detach(&logger);

    std::cout << "--- Third update ---\n";
    market.setPrice(201.75);

    return 0;
}
/*
Expected output
--- First update ---
MobileApp: AAPL price changed to 195.5
TradingTerminal: AAPL = 195.5
StockLogger: Recorded AAPL at 195.5

--- Removing terminal ---
--- Second update ---
MobileApp: AAPL price changed to 198.25
StockLogger: Recorded AAPL at 198.25

--- Removing logger ---
--- Third update ---
MobileApp: AAPL price changed to 201.75
Your challenge: implement the six TODO sections without changing main().
*/