/*
Problem: Organization Salary Calculator
Create a Composite Pattern for an organization.
You have two types of objects:
Employee
An employee has:
name
salary
An employee is a Leaf.
Department
A department can contain:
Employees
Other Departments
A department's total salary is:
sum of salaries of all children
For example:
Company
│
├── Alice       $5000
├── Bob         $6000
│
└── Engineering
    │
    ├── Charlie $7000
    ├── David   $8000
    │
    └── Backend
        ├── Eve   $9000
        └── Frank $10000
Calling:
company.GetSalary();
should return:
45000
Requirements
Implement:
class EmployeeComponent
as your common abstraction.
Then:
class Employee
as the Leaf.
And:
class Department
as the Composite.
Department should support:
Add(...)
Remove(...)
GetSalary()
Use:
std::unique_ptr
for ownership.
Important constraint
Do not use dynamic_cast.
The whole point is that:
company.GetSalary();
should work polymorphically without the caller knowing whether
it is dealing with an Employee or Department.
*/
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

class EmployeeComponent {
  public:
    virtual int GetSalary() const = 0;
    virtual ~EmployeeComponent() = default;
};

class Employee : public EmployeeComponent {
  int salary_;
  std::string name_;
  public:
  Employee(int salary, std::string name) : salary_(salary), name_(name) {}
  int GetSalary() const override {
    return salary_;
  }
};

class Department: public EmployeeComponent {
  
  std::vector<std::unique_ptr<EmployeeComponent>> units_;
  
  public:

  void Add(std::unique_ptr<EmployeeComponent> unit) {
    if(unit == nullptr) return;
    units_.push_back(std::move(unit));
  }
  
  void Remove(EmployeeComponent* unit) {
      if (unit == nullptr) return;

      auto it = std::find_if(
          units_.begin(),
          units_.end(),
          [unit](const auto& child) {
              return child.get() == unit;
          });

      if (it != units_.end()) {
          units_.erase(it);
      }
  }

  int GetSalary() const override {
    int total_salary = 0;
    for (const auto& unit : units_) {
      total_salary += unit->GetSalary();
    }
    return total_salary;
  }

};

int main() {

  std::unique_ptr<Department> it = std::make_unique<Department>();
  it->Add(std::make_unique<Employee>(10000, "John"));
  it->Add(std::make_unique<Employee>(20000, "John"));
  it->Add(std::make_unique<Employee>(35000, "John"));
  
  std::unique_ptr<Department> fin = std::make_unique<Department>();
  fin->Add(std::make_unique<Employee>(12000, "John"));
  fin->Add(std::make_unique<Employee>(22000, "John"));
  fin->Add(std::make_unique<Employee>(33000, "John"));

  std::unique_ptr<Department> software = std::make_unique<Department>();
  software->Add(std::make_unique<Employee>(40000, "John"));
  software->Add(std::make_unique<Employee>(42000, "John"));
  software->Add(std::make_unique<Employee>(55000, "John"));

  std::unique_ptr<Department> hardware = std::make_unique<Department>();
  hardware->Add(std::make_unique<Employee>(40000, "John"));
  hardware->Add(std::make_unique<Employee>(52000, "John"));
  hardware->Add(std::make_unique<Employee>(55000, "John"));

  std::unique_ptr<Department> engineering = std::make_unique<Department>();
  engineering->Add(std::move(software));
  engineering->Add(std::move(hardware));

  Department company = Department();
  company.Add(std::move(it));
  company.Add(std::move(fin));
  company.Add(std::move(engineering));
  company.Add(std::make_unique<Employee>(100000, "CEO"));
  company.Add(std::make_unique<Employee>(100000, "CTO"));
  company.Add(std::make_unique<Employee>(100000, "Founder"));
  std::cout << "company total salary: " << company.GetSalary() << std::endl;
}