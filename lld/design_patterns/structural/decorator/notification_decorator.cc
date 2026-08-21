/*
Problem: Notification System
Create a notification system using the Decorator Pattern.
You have a basic notification:
Basic Notification
It sends a message.
You need to support these optional features:
SMS
Email
Slack
The requirements:
Component
Create:
class Notification
with:
virtual void Send(const std::string& message) = 0;
Concrete Component
Create:
class BasicNotification
which prints:
Sending notification: <message>
Decorators
Create:
SMSDecorator
EmailDecorator
SlackDecorator
Each decorator should:
Wrap another Notification.
Call the wrapped notification's Send().
Then perform its own action.
For example:
EmailDecorator
       |
       v
SMSDecorator
       |
       v
BasicNotification
Calling:
notification->Send("Server is down");
should conceptually produce:
Sending notification: Server is down
Sending SMS: Server is down
Sending Email: Server is down
Additional requirement
Use:
std::unique_ptr
rather than raw pointers.
And don't look up a Decorator implementation. Try to design the class structure yourself.
*/

#include <iostream>
#include <memory>
#include <string>

class Notification {
public:
  virtual void Send(const std::string& message) const = 0;
  virtual ~Notification() = default;
};

class BasicNotification : public Notification {
public:
  void Send(const std::string& message) const override {
    std::cout << " BasicNotification is being sent\n" << message << "\n BasicNotification sent\n";
  }
};

class NotificationDecorator : public Notification {
protected:
  std::unique_ptr<Notification> notifier_;
public:
  NotificationDecorator(std::unique_ptr<Notification> notifier) : notifier_(std::move(notifier)) {}
};

class SMSNotification : public NotificationDecorator {
public:
  SMSNotification(std::unique_ptr<Notification> notifier) : NotificationDecorator(std::move(notifier)) {}
  void Send(const std::string& message) const override {
    std::cout << " SMSNotification is being sent\n" << message << "\n SMSNotification sent\n";
    notifier_->Send(message);
  }
};

class EmailNotification : public NotificationDecorator {
public:
  EmailNotification(std::unique_ptr<Notification> notifier) : NotificationDecorator(std::move(notifier)) {}
  void Send(const std::string& message) const override {
    std::cout << " EmailNotification is being sent\n" << message << "\n EmailNotification sent\n";
    notifier_->Send(message);
  }
};

class SlackNotification : public NotificationDecorator {
public:
  SlackNotification(std::unique_ptr<Notification> notifier) : NotificationDecorator(std::move(notifier)) {}
  void Send(const std::string& message) const override {
    std::cout << " SlackNotification is being sent\n" << message << "\n SlackNotification sent\n";
    notifier_->Send(message);
  }
};


int main() {
  std::unique_ptr<Notification> notification = std::make_unique<BasicNotification>();
  notification->Send(" currently only basic notification");
  std::cout << "\n";

  notification = std::make_unique<SMSNotification>(std::move(notification));
  notification->Send(" SMS as well supported notification");
  std::cout << "\n";

  notification = std::make_unique<EmailNotification>(std::move(notification));
  notification->Send(" Email as well supported notification");
  std::cout << "\n";

  notification = std::make_unique<SlackNotification>(std::move(notification));
  notification->Send(" Slack as well supported notification");
  std::cout << "\n";

  return 0;
}