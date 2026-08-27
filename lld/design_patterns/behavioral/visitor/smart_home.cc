/*
Scenario
You're building a simple smart-home device inspection system.
There are three device types:
Light
Thermostat
SecurityCamera
Different inspections need to be performed on them.
The program should support visitors such as:
PowerConsumptionVisitor
MaintenanceVisitor
Each visitor performs a different operation depending on the device type.
Starter Code
Your job is to implement the classes marked with TODO.
*/
#include <iostream>
#include <string>
#include <vector>

// ============================================================
// Your Visitor Pattern implementation goes here
// ============================================================

// Forward declarations
class Light;
class Thermostat;
class SecurityCamera;


// TODO 1:
// Create the abstract DeviceVisitor interface.

class DeviceVisitor {
public:
  virtual void visit(Light&) = 0;
  virtual void visit(Thermostat&) = 0;
  virtual void visit(SecurityCamera&) = 0;

  virtual ~DeviceVisitor() = default;
};

// TODO 2:
// Create the abstract Device interface.

class Device {
public:
  virtual void accept(DeviceVisitor&) = 0;
  virtual ~Device() = default;
};

// TODO 3:
// Create Light.
//
// Data:
//   int brightness;        // 0 - 100
//   bool isOn;
//
// Constructor:
//   Light(int brightness, bool isOn)
//
// Provide:
//   int getBrightness() const
//   bool getIsOn() const
//
// Implement accept() correctly.

class Light : public Device {

  int brightness_;
  bool isOn_;
public:
  Light(int brightness, bool isOn) 
          : brightness_(brightness), isOn_(isOn){}
  int getBrightness() const {
    return brightness_;
  }
  bool getIsOn() const {
    return isOn_;
  }

  void accept(DeviceVisitor& visitor) {
    visitor.visit(*this);
  }
};

// TODO 4:
// Create Thermostat.
//
// Data:
//   double temperature;
//   bool heating;
//
// Constructor:
//   Thermostat(double temperature, bool heating)
//
// Provide:
//   double getTemperature() const
//   bool isHeating() const
//
// Implement accept() correctly.

class Thermostat : public Device {

  double temperature_;
  bool heating_;
public:
  Thermostat(double temperature, bool heating) 
          : temperature_(temperature), heating_(heating) {}
  double getTemperature() const {
    return temperature_;
  }
  bool isHeating() const {
    return heating_;
  }

  void accept(DeviceVisitor& visitor) {
    visitor.visit(*this);
  }
};

// TODO 5:
// Create SecurityCamera.
//
// Data:
//   int recordingHours;
//   bool nightVision;
//
// Constructor:
//   SecurityCamera(int recordingHours, bool nightVision)
//
// Provide:
//   int getRecordingHours() const
//   bool hasNightVision() const
//
// Implement accept() correctly.

class SecurityCamera : public Device {
  int recordingHours_;
  bool nightVision_;
public:
  SecurityCamera(int recordingHour, bool nightVision) 
        : recordingHours_(recordingHour), nightVision_(nightVision) {}

  int getRecordingHours() const {
    return recordingHours_;
  }
  bool hasNightVision() const {
    return nightVision_;
  }

  void accept(DeviceVisitor& visitor) {
    visitor.visit(*this);
  }
};

// TODO 6:
// Create PowerConsumptionVisitor.
//
// Rules:
//
// Light:
//   if OFF -> 0 watts
//   if ON  -> 5 + brightness * 0.2 watts
//
// Thermostat:
//   if heating -> 1500 watts
//   otherwise 100 watts
//
// SecurityCamera:
//   8 watts normally
//   12 watts if night vision is enabled
//
// The visitor should keep a running total:
//
//   double totalPower;
//
// Provide:
//
//   double getTotalPower() const
//
// Implement all visit() methods.
class PowerConsumptionVisitor : public DeviceVisitor {
double totalPower_;
public:
  PowerConsumptionVisitor():totalPower_(0) {}

  void visit(Light& light) override {
    totalPower_ = totalPower_ + 
                  (light.getIsOn() ? 5 + light.getBrightness()*0.2 : 0);
  }
  void visit(Thermostat& thermostat) override {
    totalPower_ = totalPower_ +
                  (thermostat.isHeating() ? 1500 : 100);
  }
  void visit(SecurityCamera& security_camera) override {
    totalPower_ = totalPower_ +
                  (security_camera.hasNightVision() ? 12 : 8);
  }
  double getTotalPower() {
    return totalPower_;
  }
};


// TODO 7:
// Create MaintenanceVisitor.
//
// Rules:
//
// Light:
//   brightness > 90 -> print:
//   "Light requires bulb inspection"
//
// Thermostat:
//   temperature < 16 OR temperature > 30 -> print:
//   "Thermostat requires calibration"
//
// SecurityCamera:
//   recordingHours > 5000 -> print:
//   "Camera requires storage maintenance"
//
// Otherwise print nothing.
//
// Implement all visit() methods.

class MaintenanceVisitor : public DeviceVisitor {
public:
  void visit(Light& light) override {
    if(light.getBrightness() > 90) {
      std::cout << "Light requires bulb inspection\n";
    }
  }
  void visit(Thermostat& thermostat) override {
    if(thermostat.getTemperature() < 16 || thermostat.getTemperature() > 30) {
      std::cout <<"Thermostat requires calibration\n";
    }
  }
  void visit(SecurityCamera& security_camera) override {
    if(security_camera.getRecordingHours() > 5000) {
      std::cout <<"Camera requires storage maintenance\n";
    }
  }
};

// ============================================================
// DO NOT MODIFY MAIN()
// ============================================================

int main() {

    std::vector<Device*> devices;

    Light light(80, true);
    Thermostat thermostat(22.5, true);
    SecurityCamera camera(5200, true);

    devices.push_back(&light);
    devices.push_back(&thermostat);
    devices.push_back(&camera);

    PowerConsumptionVisitor powerVisitor;

    for (Device* device : devices) {
        device->accept(powerVisitor);
    }

    std::cout << "Total power: "
              << powerVisitor.getTotalPower()
              << " watts\n";


    MaintenanceVisitor maintenanceVisitor;

    for (Device* device : devices) {
        device->accept(maintenanceVisitor);
    }

    return 0;
}
/*
Your task
Implement TODO 1 → TODO 7.
The important part isn't just making it compile. Make sure you understand this flow:
Device*
│
│ accept(visitor)
↓
Concrete Device
│
│ visitor.visit(*this)
↓
Concrete Visitor
│
├── visit(Light&)
├── visit(Thermostat&)
└── visit(SecurityCamera&)
Expected output
The exact numeric formatting of the power value may depend on your cout 
settings, but semantically it should report:
Total power: 1519 watts
Camera requires storage maintenance
There should be no light maintenance message and no thermostat maintenance message.
The type relationships in the starter code are intentionally arranged so
that accept(DeviceVisitor&) and all three visit(ConcreteDevice&) overloads match correctly.
*/