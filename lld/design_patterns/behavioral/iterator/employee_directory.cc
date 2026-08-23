/*
You are given an EmployeeDirectory that stores employees internally.
The client must not directly access the internal container.
You need to implement an Iterator Design Pattern that allows the client to traverse employees.
Requirements
Each employee has:
id
name
department
salary
The directory should internally store employees however you choose.
You need to implement:
Iterator
It should support:
hasNext()
next()
EmployeeIterator
It should traverse the directory.
EmployeeDirectory
It should:
- store employees
- allow employees to be added
- expose an iterator
- NOT expose its underlying container to the client
Additional Challenge
The directory contains employees from multiple departments.
The iterator should support department filtering.
For example:
auto iterator = directory.createIterator("Engineering");
should traverse only Engineering employees.
Directory

Alice     Engineering
Bob       HR
Charlie   Engineering
David     Finance
Eve       Engineering
The Engineering iterator should produce:
Alice
Charlie
Eve
while an HR iterator should produce:
Bob
If the department is an empty string:
directory.createIterator("")
the iterator should traverse all employees.
Important
The filtering logic belongs to the Iterator, not the client.
The client should simply do:
while (iterator->hasNext()) {
    Employee employee = iterator->next();
    // ...
}
Rules for Your Implementation
You only need to implement the design-pattern-related code.
You should implement:
Employee
Iterator
EmployeeIterator
EmployeeDirectory
You may choose:
- std::vector
- raw array
- another suitable container
for the internal storage.
But do not modify main().
I've written main() below so that the expected types and ownership are consistent.
Starter Code
*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Employee {
private:
    int id_;
    std::string name_;
    std::string department_;
    double salary_;

public:
    Employee(int id,
             const std::string& name,
             const std::string& department,
             double salary)
        : id_(id),
          name_(name),
          department_(department),
          salary_(salary) {}

    int getId() const {
        return id_;
    }

    const std::string& getName() const {
        return name_;
    }

    const std::string& getDepartment() const {
        return department_;
    }

    double getSalary() const {
        return salary_;
    }
};


// ============================================================
// TODO: Implement the Iterator Design Pattern below.
// You may add forward declarations, abstract classes,
// concrete classes, methods, etc.
// Do NOT modify main().
// ============================================================
// Your Iterator abstraction

// ============================================================
// Iterator
// ============================================================

template<typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;

    virtual ~Iterator() = default;
};


// Forward declaration
class EmployeeDirectory;


// ============================================================
// Concrete Iterator
// ============================================================

class EmployeeIterator : public Iterator<Employee> {
private:
    EmployeeDirectory* employee_directory_;
    std::string department_;
    int curr_pos_;

public:
    EmployeeIterator(EmployeeDirectory* employee_directory,
                     const std::string& department)
        : employee_directory_(employee_directory),
          department_(department),
          curr_pos_(-1) {}

    bool hasNext() override;

    Employee next() override;
};


// ============================================================
// Collection
// ============================================================

class EmployeeDirectory {
private:
    std::vector<Employee> employee_;

public:
    void addEmployee(const Employee& employee);

    int numEmployee() const;

    Employee getEmployeeAt(int pos) const;

    std::unique_ptr<Iterator<Employee>>
    createIterator(const std::string& department);
};


// ============================================================
// EmployeeDirectory implementation
// ============================================================

void EmployeeDirectory::addEmployee(const Employee& employee) {
    employee_.push_back(employee);
}

int EmployeeDirectory::numEmployee() const {
    return static_cast<int>(employee_.size());
}

Employee EmployeeDirectory::getEmployeeAt(int pos) const {
    return employee_[pos];
}

std::unique_ptr<Iterator<Employee>>
EmployeeDirectory::createIterator(const std::string& department) {
    return std::make_unique<EmployeeIterator>(this, department);
}


// ============================================================
// EmployeeIterator implementation
// ============================================================

bool EmployeeIterator::hasNext() {

    int next_pos = curr_pos_ + 1;

    while (next_pos < employee_directory_->numEmployee()) {

        const Employee employee =
            employee_directory_->getEmployeeAt(next_pos);

        // Empty department means:
        // return every employee.
        if (department_.empty() ||
            employee.getDepartment() == department_) {

            return true;
        }

        ++next_pos;
    }

    return false;
}

Employee EmployeeIterator::next() {

    ++curr_pos_;

    while (curr_pos_ < employee_directory_->numEmployee()) {

        const Employee employee =
            employee_directory_->getEmployeeAt(curr_pos_);

        if (department_.empty() ||
            employee.getDepartment() == department_) {

            return employee;
        }

        ++curr_pos_;
    }

    // next() should normally only be called when hasNext() is true.
    // This return is here to satisfy the function's return type.
    throw std::out_of_range("Iterator has no next element");
}
// ============================================================
// DO NOT MODIFY main()
// ============================================================

int main() {
    EmployeeDirectory directory;

    directory.addEmployee(
        Employee(101, "Alice", "Engineering", 95000));

    directory.addEmployee(
        Employee(102, "Bob", "HR", 70000));

    directory.addEmployee(
        Employee(103, "Charlie", "Engineering", 105000));

    directory.addEmployee(
        Employee(104, "David", "Finance", 85000));

    directory.addEmployee(
        Employee(105, "Eve", "Engineering", 115000));

    std::cout << "=== All Employees ===\n";

    {
        std::unique_ptr<Iterator<Employee>> iterator =
            directory.createIterator("");

        while (iterator->hasNext()) {
            Employee employee = iterator->next();

            std::cout << employee.getId() << " "
                      << employee.getName() << " "
                      << employee.getDepartment() << " "
                      << employee.getSalary() << '\n';
        }
    }

    std::cout << "\n=== Engineering Employees ===\n";

    {
        std::unique_ptr<Iterator<Employee>> iterator =
            directory.createIterator("Engineering");

        while (iterator->hasNext()) {
            Employee employee = iterator->next();

            std::cout << employee.getId() << " "
                      << employee.getName() << " "
                      << employee.getDepartment() << " "
                      << employee.getSalary() << '\n';
        }
    }

    std::cout << "\n=== HR Employees ===\n";

    {
        std::unique_ptr<Iterator<Employee>> iterator =
            directory.createIterator("HR");

        while (iterator->hasNext()) {
            Employee employee = iterator->next();

            std::cout << employee.getId() << " "
                      << employee.getName() << " "
                      << employee.getDepartment() << " "
                      << employee.getSalary() << '\n';
        }
    }

    return 0;
}
/*
Expected output
=== All Employees ===
101 Alice Engineering 95000
102 Bob HR 70000
103 Charlie Engineering 105000
104 David Finance 85000
105 Eve Engineering 115000

=== Engineering Employees ===
101 Alice Engineering 95000
103 Charlie Engineering 105000
105 Eve Engineering 115000

=== HR Employees ===
102 Bob HR 70000
What makes this a good Iterator challenge
You need to figure out several things yourself:
1. What should the Iterator interface look like?
2. Should it be a template?
3. How should EmployeeIterator access the directory's data?
4. Where should the current traversal position be stored?
5. Where should department filtering happen?
6. How should createIterator() return ownership safely?
7. How do you make EmployeeDirectory and EmployeeIterator
work together without exposing the internal container to main()?

One important constraint: main() is intentionally written
against std::unique_ptr<Iterator<Employee>>, so your Iterator 
abstraction needs to match that exact type. I have also checked 
the Employee return type, createIterator() return type, and 
model for consistency.
*/