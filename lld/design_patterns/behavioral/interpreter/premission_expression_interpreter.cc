/*
Problem: Permission Expression Interpreter
We want to build a tiny permission language.
The language supports:
permission
permission AND permission
permission OR permission
NOT permission
For example:
READ AND WRITE
or:
READ OR WRITE
or:
NOT DELETE
The context contains the permissions currently granted to a user.
For example:
READ = true
WRITE = false
DELETE = false
Then:
READ AND WRITE
evaluates to:
false
while:
READ OR WRITE
evaluates to:
true
Requirements
You need to implement these classes:
PermissionExpression
PermissionContext
Permission
AndExpression
OrExpression
NotExpression

PermissionExpression
Abstract base class.
It should expose something equivalent to:
virtual bool interpret(PermissionContext& context) = 0;
PermissionContext
Stores whether a permission is granted.

It should support permissions represented by strings such as:
"READ"
"WRITE"
"DELETE"
"ADMIN"
For example:
context.setPermission("READ", true);
and:
context.hasPermission("READ");
should return:
true

Permission
Terminal expression.
Example:
Permission("READ")
should interpret itself by asking the context whether READ is granted.
AndExpression
Represents:
left AND right
It should contain two PermissionExpressions.
Example:
READ AND WRITE
OrExpression
Represents:
left OR right
NotExpression
Represents:
NOT expression
It should contain one PermissionExpression.
Importantly, it should be possible to nest expressions.
For example:
NOT (READ AND WRITE)
should be representable as:
          NOT
           |
          AND
         /   \
      READ   WRITE
Constraints
Use:
- polymorphism
- abstract base class
- composition
- smart pointers (std::unique_ptr)
- override
- proper virtual destructor
Do not implement a parser.
The expression tree will be constructed manually.
Your job is specifically to implement the Interpreter Pattern, not expression parsing.
Starter Code
Everything below // YOUR CODE HERE is the part you need to implement.
Do not change main().
*/

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ============================================================
// YOUR CODE HERE
// Implement the Interpreter Design Pattern
// ============================================================

// TODO 1:
// Create the PermissionContext class.
//
// It should:
//   - store permission name -> granted/not granted
//   - provide a way to set a permission
//   - provide a way to check whether a permission is granted

class PermissionContext {
  std::unordered_map<std::string, bool> context_;
public:
  void setPermission(const std::string& permission, bool value) {
    context_[permission] = value;
  }

  bool getPermission(const std::string& permission) {
    auto it = context_.find(permission);

    if (it == context_.end()) {
        return false;
    }

    return it->second;
  }
};


// TODO 2:
// Create the abstract PermissionExpression class.
//
// It should:
//   - declare interpret(PermissionContext&)
//   - return bool
//   - have a virtual destructor
class PermissionExpression {
public:
  virtual bool interpret(PermissionContext&) = 0;
  virtual ~PermissionExpression() = default;
};


// TODO 3:
// Create the terminal expression:
//
// Permission
//
// Example:
//     Permission("READ")
//     Permission("WRITE")
//
// interpret() should ask the context whether
// this permission is granted.
class Permission : public PermissionExpression {
  std::string permission_;
public:
  Permission(const std::string& permission)
            : permission_(permission) {}
  bool interpret(PermissionContext& permission_context) override {
    return permission_context.getPermission(permission_);
  }
};


// TODO 4:
// Create the non-terminal expression:
//
// AndExpression
//
// It should contain:
//     left expression
//     right expression
//
// Example:
//     READ AND WRITE
//
// interpret() should return:
//     left->interpret(context) &&
//     right->interpret(context)
class AndExpression : public PermissionExpression {
  std::unique_ptr<PermissionExpression> left_;
  std::unique_ptr<PermissionExpression> right_;
public:
  AndExpression(std::unique_ptr<PermissionExpression> left,
                std::unique_ptr<PermissionExpression> right)
                :left_(std::move(left)), right_(std::move(right)) {}
  bool interpret(PermissionContext& permission_context) override {
    return left_->interpret(permission_context) && right_->interpret(permission_context);
  }
};

// TODO 5:
// Create the non-terminal expression:
//
// OrExpression
//
// Example:
//     READ OR WRITE
class OrExpression : public PermissionExpression {
  std::unique_ptr<PermissionExpression> left_;
  std::unique_ptr<PermissionExpression> right_;
public:
  OrExpression(std::unique_ptr<PermissionExpression> left,
                std::unique_ptr<PermissionExpression> right)
                :left_(std::move(left)), right_(std::move(right)) {}
  bool interpret(PermissionContext& permission_context) override {
    return left_->interpret(permission_context) || right_->interpret(permission_context);
  }
};


// TODO 6:
// Create the non-terminal expression:
//
// NotExpression
//
// Example:
//     NOT READ
//
// It should contain one PermissionExpression.
//
// It must also support nested expressions, such as:
//
//     NOT (READ AND WRITE)
class NotExpression : public PermissionExpression {
  std::unique_ptr<PermissionExpression> expression_;
public:
  NotExpression(std::unique_ptr<PermissionExpression> expression)
                :expression_(std::move(expression)){}
  bool interpret(PermissionContext& permission_context) override {
    return !expression_->interpret(permission_context);
  }
};


// ============================================================
// DO NOT MODIFY MAIN
// ============================================================

int main() {

    PermissionContext context;

    context.setPermission("READ", true);
    context.setPermission("WRITE", false);
    context.setPermission("DELETE", false);
    context.setPermission("ADMIN", true);

    // --------------------------------------------------------
    // Expression 1:
    //
    // READ AND WRITE
    //
    // Expected: false
    // --------------------------------------------------------

    std::unique_ptr<PermissionExpression> expression1 =
        std::make_unique<AndExpression>(
            std::make_unique<Permission>("READ"),
            std::make_unique<Permission>("WRITE")
        );

    std::cout << "Expression 1: "
              << std::boolalpha
              << expression1->interpret(context)
              << '\n';


    // --------------------------------------------------------
    // Expression 2:
    //
    // READ OR WRITE
    //
    // Expected: true
    // --------------------------------------------------------

    std::unique_ptr<PermissionExpression> expression2 =
        std::make_unique<OrExpression>(
            std::make_unique<Permission>("READ"),
            std::make_unique<Permission>("WRITE")
        );

    std::cout << "Expression 2: "
              << expression2->interpret(context)
              << '\n';


    // --------------------------------------------------------
    // Expression 3:
    //
    // NOT DELETE
    //
    // Expected: true
    // --------------------------------------------------------

    std::unique_ptr<PermissionExpression> expression3 =
        std::make_unique<NotExpression>(
            std::make_unique<Permission>("DELETE")
        );

    std::cout << "Expression 3: "
              << expression3->interpret(context)
              << '\n';


    // --------------------------------------------------------
    // Expression 4:
    //
    // NOT (READ AND WRITE)
    //
    // READ  = true
    // WRITE = false
    //
    // READ AND WRITE = false
    // NOT false       = true
    //
    // Expected: true
    // --------------------------------------------------------

    std::unique_ptr<PermissionExpression> expression4 =
        std::make_unique<NotExpression>(
            std::make_unique<AndExpression>(
                std::make_unique<Permission>("READ"),
                std::make_unique<Permission>("WRITE")
            )
        );

    std::cout << "Expression 4: "
              << expression4->interpret(context)
              << '\n';


    // --------------------------------------------------------
    // Expression 5:
    //
    // (READ AND ADMIN) OR DELETE
    //
    // READ  = true
    // ADMIN = true
    // DELETE = false
    //
    // READ AND ADMIN = true
    // true OR false  = true
    //
    // Expected: true
    // --------------------------------------------------------

    std::unique_ptr<PermissionExpression> expression5 =
        std::make_unique<OrExpression>(
            std::make_unique<AndExpression>(
                std::make_unique<Permission>("READ"),
                std::make_unique<Permission>("ADMIN")
            ),
            std::make_unique<Permission>("DELETE")
        );

    std::cout << "Expression 5: "
              << expression5->interpret(context)
              << '\n';


    return 0;
}
/*
Expected output
Expression 1: false
Expression 2: true
Expression 3: true
Expression 4: true
Expression 5: true

Challenge: implement the six pieces without touching main().
The key design question is how your non-terminal expressions
should own their child expressions while still allowing arbitrary nesting.
*/
