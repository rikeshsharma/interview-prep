/*
Problem: Expense Approval Chain
You're building an expense approval system.
An employee submits an expense.
Different managers have different approval limits:
TeamLead       → up to ₹10,000
Manager        → up to ₹50,000
Director       → up to ₹2,00,000
The chain should be:
TeamLead
   ↓
Manager
   ↓
Director
When an expense arrives:
- If TeamLead can approve it, TeamLead approves it.
- Otherwise, it passes to Manager.
- If Manager can approve it, Manager approves it.
- Otherwise, it passes to Director.
- If Director cannot approve it either, the request is rejected.
Your Job
Implement only these classes:
class ExpenseRequest;

class ExpenseHandler;

class TeamLead;

class Manager;

class Director;
You are free to decide:
- what fields ExpenseRequest contains
- whether you use references, pointers, or smart pointers
- how setNext() works
- how the handler interface looks
- how the chain is connected
But it must genuinely implement Chain of Responsibility, rather than simply putting all approval logic into one class.
Requirements
Your implementation should support:
₹5,000      → TeamLead
₹25,000     → Manager
₹1,50,000   → Director
₹3,00,000   → Rejected
The chain should be constructed externally.
main() — Don't Modify This
Your code should compile against this exact main():
int main() {
    TeamLead teamLead;
    Manager manager;
    Director director;

    teamLead.setNext(&manager);
    manager.setNext(&director);

    ExpenseRequest r1(5000);
    ExpenseRequest r2(25000);
    ExpenseRequest r3(150000);
    ExpenseRequest r4(300000);

    teamLead.handle(r1);
    teamLead.handle(r2);
    teamLead.handle(r3);
    teamLead.handle(r4);

    return 0;
}
Expected behavior
TeamLead approved expense of 5000
Manager approved expense of 25000
Director approved expense of 150000
Expense of 300000 rejected
Your task: write everything needed above main().
Don't worry about making it production-grade yet. Focus on getting the pattern structure right.
Once you send your implementation, I'll review it, point out any design issues, and then give you Challenge 2 with increased difficulty.
*/
#include <iostream>
#include <string>

class ExpenseRequest {
  // amount of money
  int expense_; 
public:
  ExpenseRequest(int expense) {
    if(expense < 0) {
      std::cout << "Expense cannot be negative!!\n";
      std::cout << "Setting expense amount to ₹0\n";
      expense_ = 0;
      return;
    }
    expense_ = expense;
  }

  int GetExpense() {
    return expense_;
  }

};

class ExpenseHandler {
protected:
  ExpenseHandler* handler_;
public:
  void SetNext(ExpenseHandler* handler) {
    handler_ = handler;
  }
  virtual void Handle(ExpenseRequest& request) const = 0;
  ExpenseHandler(): handler_(nullptr) {}
  virtual ~ExpenseHandler() = default;
};

class TeamLead : public ExpenseHandler {
public:
  void Handle(ExpenseRequest& request) const override {
    if (request.GetExpense() <= 10000) {
      std::cout <<"TeamLead approved expense of " << request.GetExpense() << "\n";
      return;
    }
    handler_->Handle(request);
  }
};

class Manager : public ExpenseHandler {
public:
  void Handle(ExpenseRequest& request) const override {
    if (request.GetExpense() <= 50000) {
      std::cout <<"Manager approved expense of " << request.GetExpense() << "\n";
      return;
    }
    handler_->Handle(request);
  }
};

class Director : public ExpenseHandler {
public:
  void Handle(ExpenseRequest& request) const override {
    if (request.GetExpense() <= 200000) {
      std::cout <<"Director approved expense of " << request.GetExpense() << "\n";
      return;
    }
    std::cout << "Expense of "<<request.GetExpense() <<" rejected\n";
  }
};


int main() {
    TeamLead teamLead;
    Manager manager;
    Director director;

    teamLead.SetNext(&manager);
    manager.SetNext(&director);

    ExpenseRequest r1(5000);
    ExpenseRequest r2(25000);
    ExpenseRequest r3(150000);
    ExpenseRequest r4(300000);

    teamLead.Handle(r1);
    teamLead.Handle(r2);
    teamLead.Handle(r3);
    teamLead.Handle(r4);

    return 0;
}