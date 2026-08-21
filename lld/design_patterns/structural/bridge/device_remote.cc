/*
Scenario
You are building a simple remote control system.
There are two independent dimensions.
Devices
TV
Radio
Remotes
BasicRemote
AdvancedRemote
Your design should allow:
BasicRemote + TV
BasicRemote + Radio

AdvancedRemote + TV
AdvancedRemote + Radio
Requirements
Create:
1. Device
It should have operations such as:
IsEnabled()
Enable()
Disable()
SetVolume()
2. Concrete devices
TV
Radio
Each should implement Device.
3. Remote
The remote should contain a reference/pointer to Device.
It should provide operations such as:
TogglePower()
VolumeUp()
VolumeDown()
4. BasicRemote
Inherit from Remote.
5. AdvancedRemote
Inherit from Remote.
Give AdvancedRemote one additional feature:
Mute()
Your target structure
             Remote
            /      \
           /        \
 BasicRemote     AdvancedRemote
           \        /
            \      /
              Device
             /     \
            /       \
           TV      Radio
The important constraint is:
Do NOT create TVRemote, RadioRemote, AdvancedTVRemote, etc.

Your final main() should demonstrate at least:
TV tv;
Radio radio;

BasicRemote basic(tv);
basic.TogglePower();

AdvancedRemote advanced(radio);
advanced.TogglePower();
advanced.Mute();
*/

#include <iostream>

class Device {
  protected:
    bool enabled;
    unsigned int volume;

  public:
    Device() : enabled(false), volume(0) {}
    virtual ~Device() = default;

    virtual bool IsEnabled() = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void SetVolume(unsigned int vol) = 0;
    virtual unsigned int GetVolume() = 0;
};

class TV : public Device { 
  public:
    bool IsEnabled() override {
      return enabled;
    }

    void Enable() override {
      enabled = true;
    }
    void Disable() override {
      enabled = false;
    }
    void SetVolume(unsigned int vol) override {
      if(vol < 0 || vol > 100) {
        std::cout << "Volume between range 0 and 100 can be set \n";
        std::cout << "You entered: " << vol <<"\n";
        std::cout << "Cannot set this volume!";
        return;
      }
      volume = vol;
    }

    unsigned int GetVolume() override {
      return volume;
    }
  
};

class Radio : public Device { 
  public:
    bool IsEnabled() override {
      return enabled;
    }

    void Enable() override {
      enabled = true;
    }

    void Disable() override {
      enabled = false;
    }

    void SetVolume(unsigned int vol) override {
      if(vol < 0 || vol > 20) {
        std::cout << "Volume between range 0 and 20 can be set \n";
        std::cout << "You entered: " << vol <<"\n";
        std::cout << "Cannot set this volume!";
        return;
      }
      volume = vol;
    }

    unsigned int GetVolume() override {
      return volume;
    }
  
};
class Remote {
  protected:
    Device& device;

  public:
    Remote(Device& _device) : device(_device) {}
    virtual ~Remote() = default;

    virtual void TogglePower() = 0;
    virtual void VolumeUp() = 0;
    virtual void VolumeDown() = 0;
};

class BasicRemote : public Remote {
  public:
    BasicRemote(Device& _device) : Remote(_device) {}

    void TogglePower() override {
      if(device.IsEnabled()) {
        std::cout << " Turned off\n";
        device.Disable();
      } else {
        std::cout << " Turned on\n";
        device.Enable();
      }
    }

    void VolumeUp() override {
      device.SetVolume(device.GetVolume()+1);
    }

    void VolumeDown() override {
      device.SetVolume(device.GetVolume()-1);
    }
};

class AdvancedRemote : public BasicRemote {
  public:
    AdvancedRemote(Device& _device) : BasicRemote(_device) {}
    void Mute() {
      device.SetVolume(0);
      std::cout << " Muted!!\n";
    }
};

int main() {
  TV tv;
  Radio radio;
  
  BasicRemote basic(tv);
  basic.TogglePower();
  
  AdvancedRemote advanced(radio);
  advanced.TogglePower();
  basic.TogglePower();
  advanced.Mute();
  advanced.TogglePower();
}

