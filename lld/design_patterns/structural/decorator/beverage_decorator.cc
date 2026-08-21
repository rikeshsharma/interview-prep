/*
Problem: Coffee Ordering System
Create this hierarchy:
                     Beverage
                        ▲
             ┌──────────┴──────────┐
             │                     │
       SimpleCoffee          BeverageDecorator
                                  ▲
                         ┌────────┼────────┐
                         │        │        │
                       Milk      Sugar    WhippedCream
Beverage
It should provide:
virtual int GetCost() const = 0;
virtual std::string GetDescription() const = 0;
SimpleCoffee
Return:
Cost: 50
Description: "Coffee"
Decorators
Milk
+20
Sugar
+10
WhippedCream
+30
For example:
auto beverage = std::make_unique<SimpleCoffee>();

beverage = std::make_unique<MilkDecorator>(
    std::move(beverage));

beverage = std::make_unique<SugarDecorator>(
    std::move(beverage));
Then:
beverage->GetCost();
should return:
80
and:
beverage->GetDescription();
should return:
Coffee, Milk, Sugar
The important part
Your decorators must obtain the existing value from the wrapped object:
int GetCost() const override {
    // get wrapped cost
    // add your cost
}
and:
std::string GetDescription() const override {
    // get wrapped description
    // add your description
}
Constraint
Don't create separate classes such as:
CoffeeWithMilk
CoffeeWithMilkAndSugar
CoffeeWithMilkSugarAndCream
Use only the Decorator pattern.
This one will test whether you understand how information flows through a decorator chain, rather than just knowing the class structure.
*/
#include <iostream>
#include <string>
#include <memory>

class Beverage {
public:
  virtual int GetCost() const = 0;
  virtual std::string GetDescription() const = 0;
  virtual ~Beverage() = default;
};

class SimpleCoffee : public Beverage {
public:
  int GetCost() const override {
    return 50;
  }
  std::string GetDescription() const override {
    return "Coffee";
  }
};

class BeverageDecorator : public Beverage {
protected:
  std::unique_ptr<Beverage> beverage_;
public:
  BeverageDecorator(std::unique_ptr<Beverage> beverage) : beverage_(std::move(beverage)) {}
};

class MilkDecorator : public BeverageDecorator {
public:
  MilkDecorator(std::unique_ptr<Beverage> beverage) : BeverageDecorator(std::move(beverage)) {}
  int GetCost() const override {
    return beverage_->GetCost()+20;
  }
  std::string GetDescription() const override {
    return beverage_->GetDescription() + ", Milk";
  }
};

class SugarDecorator : public BeverageDecorator {
public:
  SugarDecorator(std::unique_ptr<Beverage> beverage) : BeverageDecorator(std::move(beverage)) {}
  int GetCost() const override {
    return beverage_->GetCost()+10;
  }
  std::string GetDescription() const override {
    return beverage_->GetDescription() + ", Sugar";
  }
};

class WhippedCreamDecorator : public BeverageDecorator {
public:
  WhippedCreamDecorator(std::unique_ptr<Beverage> beverage) : BeverageDecorator(std::move(beverage)) {}
  int GetCost() const override {
    return beverage_->GetCost()+30;
  }
  std::string GetDescription() const override {
    return beverage_->GetDescription() + ", WhippedCream";
  }
};


int main() {
  std::unique_ptr<Beverage> beverage = std::make_unique<SimpleCoffee>();

  beverage = std::make_unique<MilkDecorator>(
    std::move(beverage));

  beverage = std::make_unique<SugarDecorator>(
    std::move(beverage));

  std::cout<<beverage->GetCost()<<"\n";
  std::cout<<beverage->GetDescription()<<"\n";

  return 0;
}