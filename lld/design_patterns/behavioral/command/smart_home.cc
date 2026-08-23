/*
Scenario
We have a Smart Home system.
There are two receivers:
Light
Fan
The system should support these commands:
TurnLightOn
TurnLightOff
TurnFanOn
TurnFanOff
A RemoteControl acts as the Invoker.
Your task is to implement:
- Command
- TurnLightOnCommand
- TurnLightOffCommand
- TurnFanOnCommand
- TurnFanOffCommand
- RemoteControl
You do not need to implement Light or Fan.
You also must not modify main().
Starter code
*/
#include <iostream>
#include <string>

// ===============================
// DO NOT MODIFY THESE CLASSES
// ===============================

class Light {
public:
    void on() {
        std::cout << "Light is ON\n";
    }

    void off() {
        std::cout << "Light is OFF\n";
    }
};

class Fan {
public:
    void on() {
        std::cout << "Fan is ON\n";
    }

    void off() {
        std::cout << "Fan is OFF\n";
    }
};

// ===============================
// IMPLEMENT COMMAND PATTERN HERE
// ===============================

// 1. Command
// 2. Concrete Commands
// 3. RemoteControl
class Command {
public:
  virtual void execute() = 0;
  virtual ~Command() = default;
};

class TurnLightOnCommand : public Command {
Light& light_;
public:
  TurnLightOnCommand(Light& light) : light_(light) {}
  void execute() override {
    light_.on();
  }
};

class TurnLightOffCommand : public Command {
Light& light_;
public:
  TurnLightOffCommand(Light& light) : light_(light) {}
  void execute() override {
    light_.off();
  }
};

class TurnFanOnCommand : public Command {
Fan& fan_;
public:
  TurnFanOnCommand(Fan& fan) : fan_(fan) {}
  void execute() override {
    fan_.on();
  }
};

class TurnFanOffCommand : public Command {
Fan& fan_;
public:
  TurnFanOffCommand(Fan& fan) : fan_(fan) {}
  void execute() override {
    fan_.off();
  }
};

class RemoteControl {
  Command * command_;
public:
  RemoteControl() : command_(nullptr) {}
  void setCommand(Command* command) {
    command_ = command;
  }

  void pressButton() const {
    if (command_) {
      command_->execute();
    }
  }
};
// ===============================
// DO NOT MODIFY MAIN()
// ===============================

int main() {
    Light light;
    Fan fan;

    TurnLightOnCommand lightOn(light);
    TurnLightOffCommand lightOff(light);

    TurnFanOnCommand fanOn(fan);
    TurnFanOffCommand fanOff(fan);

    RemoteControl remote;

    remote.setCommand(&lightOn);
    remote.pressButton();

    remote.setCommand(&lightOff);
    remote.pressButton();

    remote.setCommand(&fanOn);
    remote.pressButton();

    remote.setCommand(&fanOff);
    remote.pressButton();

    return 0;
}
/*
Expected output
Light is ON
Light is OFF
Fan is ON
Fan is OFF
Constraints
1. Use inheritance for the Command interface.
2. RemoteControl must not know about Light or Fan.
3. RemoteControl should only work with Command.
4. The concrete commands should hold references to their respective receivers.
5. Don't put the actual Light/Fan operations inside RemoteControl.
6. Don't modify main().
7. Use proper virtual destructors.
Your task: write the missing classes.
*/