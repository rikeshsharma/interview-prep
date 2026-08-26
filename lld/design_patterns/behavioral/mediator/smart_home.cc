/*
Scenario: Smart Home Mediator
You are implementing a small smart-home system.
There are three devices:
Light
Thermostat
SecuritySystem
They must not directly communicate with one another.
Instead, they communicate through:
SmartHomeMediator
Required behavior
1. Light
The light can:
turnOn()
turnOff()
When the light is turned on, it should notify the mediator.
2. Thermostat
The thermostat can:
setTemperature(int temperature)
When temperature changes, it should notify the mediator.
3. Security System
The security system can:
arm()
disarm()
When its state changes, it should notify the mediator.
Business Rules
The mediator must enforce these rules:
Rule A — Security
When the security system is armed:
Light → OFF
Thermostat → 18°C
Rule B — Security disarmed
When security becomes disarmed:
Light → ON
The thermostat should remain at its current temperature.
Rule C — High temperature
When the thermostat is set above 30°C:
Security → ARM
The mediator should trigger this.
Rule D — Low temperature
When the thermostat is set below 16°C:
Light → ON
Important Constraint
The devices must not directly reference each other.
For example, this is forbidden:
class Light {
    Thermostat* thermostat;   // ❌
    SecuritySystem* security; // ❌
};
And this is also forbidden:
light.turnOff();
from inside Thermostat.
Communication must go through:
Mediator
Your Task
Implement only the Mediator-pattern-related classes.
You need to implement:
class SmartHomeMediator;
class SmartDevice;
class Light;
class Thermostat;
class SecuritySystem;
You may add helper methods/data members if necessary.
You must use
- Abstract SmartHomeMediator
- Abstract/base SmartDevice
- Concrete SmartHomeController
- Concrete device classes
- Polymorphism
- Mediator-based communication
Do NOT implement main()
I will provide it for you below.
*/

#include <iostream>
#include <string>

class SmartHomeMediator;
class SmartDevice;

// ============================================================
// Mediator
// ============================================================

class SmartHomeMediator
{
public:
  virtual void notify(
      SmartDevice *sender,
      const std::string &event) = 0;

  virtual ~SmartHomeMediator() = default;
};

// ============================================================
// Colleague
// ============================================================

class SmartDevice
{
protected:
  SmartHomeMediator *mediator_;

public:
  explicit SmartDevice(SmartHomeMediator *mediator)
      : mediator_(mediator) {}

  virtual ~SmartDevice() = default;
};

// ============================================================
// Concrete Colleague: Light
// ============================================================

class Light : public SmartDevice
{
private:
  bool state_;

public:
  explicit Light(SmartHomeMediator *mediator)
      : SmartDevice(mediator), state_(false) {}

  void turnOn()
  {
    if (state_)
    {
      return;
    }

    state_ = true;
    std::cout << "Light turned ON\n";
  }

  void turnOff()
  {
    if (!state_)
    {
      return;
    }

    state_ = false;
    std::cout << "Light turned OFF\n";
  }

  bool getState() const
  {
    return state_;
  }
};

// ============================================================
// Concrete Colleague: Thermostat
// ============================================================

class Thermostat : public SmartDevice
{
private:
  int temperature_;

public:
  explicit Thermostat(SmartHomeMediator *mediator)
      : SmartDevice(mediator), temperature_(20) {}

  void setTemperature(int temperature)
  {
    temperature_ = temperature;

    std::cout << "Thermostat set to "
              << temperature_
              << "°C\n";

    mediator_->notify(this, "temperature_changed");
  }

  int getTemperature() const
  {
    return temperature_;
  }
};

// ============================================================
// Concrete Colleague: Security System
// ============================================================

class SecuritySystem : public SmartDevice
{
private:
  bool armed_;

public:
  explicit SecuritySystem(SmartHomeMediator *mediator)
      : SmartDevice(mediator), armed_(false) {}

  void arm()
  {
    if (armed_)
    {
      return;
    }

    armed_ = true;

    std::cout << "Security system ARMED\n";

    mediator_->notify(this, "security_armed");
  }

  void disarm()
  {
    if (!armed_)
    {
      return;
    }

    armed_ = false;

    std::cout << "Security system DISARMED\n";

    mediator_->notify(this, "security_disarmed");
  }

  bool isArmed() const
  {
    return armed_;
  }
};

// ============================================================
// Concrete Mediator
// ============================================================

class SmartHomeController : public SmartHomeMediator
{
private:
  Light *light_ = nullptr;
  Thermostat *thermostat_ = nullptr;
  SecuritySystem *security_system_ = nullptr;

public:
  void setLight(Light *light)
  {
    light_ = light;
  }

  void setThermostat(Thermostat *thermostat)
  {
    thermostat_ = thermostat;
  }

  void setSecuritySystem(SecuritySystem *security_system)
  {
    security_system_ = security_system;
  }

  void notify(
      SmartDevice *sender,
      const std::string &event) override
  {

    // ----------------------------------------------------
    // Thermostat changed
    // ----------------------------------------------------

    if (sender == thermostat_)
    {

      if (event == "temperature_changed")
      {

        int temperature = thermostat_->getTemperature();

        // Temperature above 30°C -> arm security
        if (temperature > 30)
        {
          security_system_->arm();
        }

        // Temperature below 16°C -> turn light on
        else if (temperature < 16)
        {
          light_->turnOn();
        }
      }
    }

    // ----------------------------------------------------
    // Security system changed
    // ----------------------------------------------------

    else if (sender == security_system_)
    {

      // Security armed:
      // Light OFF
      // Thermostat 18°C

      if (event == "security_armed")
      {

        light_->turnOff();
        thermostat_->setTemperature(18);
      }

      // Security disarmed:
      // Light ON
      // Thermostat remains unchanged

      else if (event == "security_disarmed")
      {

        light_->turnOn();
      }
    }
  }
};

// ============================================================
// Main
// ============================================================

int main()
{
  SmartHomeController controller;

  Light light(&controller);
  Thermostat thermostat(&controller);
  SecuritySystem security(&controller);

  controller.setLight(&light);
  controller.setThermostat(&thermostat);
  controller.setSecuritySystem(&security);

  std::cout << "Initial state:\n";

  light.turnOff();
  thermostat.setTemperature(22);
  security.disarm();

  std::cout << "\n--- Arming security ---\n";
  security.arm();

  std::cout << "\n--- Changing temperature to 35 ---\n";
  thermostat.setTemperature(35);

  std::cout << "\n--- Disarming security ---\n";
  security.disarm();

  std::cout << "\n--- Setting temperature to 15 ---\n";
  thermostat.setTemperature(15);

  return 0;
}

/*
Expected conceptual flow
You should end up with something roughly like:
                   SmartHomeController
                  /        |          \
                 /         |           \
              Light    Thermostat    Security
                ↑           ↑            ↑
                └───────────┴────────────┘
                       notifications
The important challenge is that the controller must coordinate the 
devices without the devices knowing about each other.
Also pay attention to event strings and state changes: avoid accidentally 
creating recursive notification loops such as:
Security.arm()
   ↓
Mediator
   ↓
Thermostat.setTemperature()
   ↓
Mediator
   ↓
Security.arm()
   ↓
...
Design your implementation so the state changes settle cleanly.
One more thing: I checked the main() against the intended interfaces 
and types—SmartHomeController is passed as a SmartHomeMediator*, and each 
concrete device is passed to the controller through the expected SmartDevice* 
relationship, so there is no intentional type mismatch in the supplied skeleton.
*/