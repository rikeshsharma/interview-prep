/*
Smart Home Event Handling
We are building a SmartHomeHub.
The hub receives events from smart devices:
"door_opened"
"motion_detected"
"temperature_high"
The hub itself should not know what to do with these events.
Instead, it delegates event handling to an EventDelegate.

There can be different delegates:
SmartHomeHub
      |
      ↓
EventDelegate
      |
      ├── SecurityDelegate
      └── ComfortDelegate

Requirements
You need to implement:

1. SmartEvent
It should store:
std::string deviceName;
std::string event;
int value;
For example:
deviceName = "Front Door"
event      = "opened"
value      = 0

2. EventDelegate
Create an abstract interface with:
virtual void handleEvent(const SmartEvent& event) = 0;
virtual ~EventDelegate() = default;

3. SecurityDelegate
It should handle:
"door_opened"
"motion_detected"
Expected behavior:
[Security] Door opened by Front Door
[Security] Motion detected by Hallway Camera
For other events, it should print:
[Security] Ignored event: temperature_high

4. ComfortDelegate
It should handle:
"temperature_high"
The value represents temperature.
For example:
value = 32
should produce:
[Comfort] High temperature detected: 32C
For events it doesn't understand:
[Comfort] Ignored event: door_opened

5. SmartHomeHub
The hub must contain an EventDelegate.
It should provide:
void setDelegate(EventDelegate* delegate);
and:
void receiveEvent(const SmartEvent& event);
receiveEvent() must delegate the event to the current delegate.
If there is no delegate, it should safely print:
[Hub] No delegate configured

Your Task
Implement everything marked TODO.
Do not modify main().
I've deliberately made the event type a const SmartEvent& everywhere 
so there is no accidental SmartEvent vs SmartEvent& / pointer type mismatch.
*/

#include <iostream>
#include <string>

// ============================================================
// YOUR CODE HERE
// Implement the Delegate Design Pattern
// ============================================================


// TODO 1:
// Create the SmartEvent class.
//
// It should store:
//   - deviceName : std::string
//   - event      : std::string
//   - value      : int
//
// Provide a constructor to initialize all three values.
//
// You may make the data private and provide getters,
// or expose them through appropriate public methods.
class SmartEvent {
  std::string deviceName;
  std::string event;
  int value;
public:
  SmartEvent(const std::string& device_name,
                const std::string& event_name,
                const int val) : deviceName(device_name),
                           event(event_name),
                           value(val) {}
  const std::string getDeviceName() const {
    return deviceName;
  }
  const std::string getEvent() const {
    return event;
  }
  const int getValue() const {
    return value;
  }
};


// TODO 2:
// Create the abstract EventDelegate interface.
//
// It should contain:
//
// virtual void handleEvent(const SmartEvent& event) = 0;
//
// and a virtual destructor.

class EventDelegate {
public:
  virtual void handleEvent(const SmartEvent& event) const = 0;
  virtual ~EventDelegate() = default;
};

// TODO 3:
// Create SecurityDelegate.
//
// It should inherit from EventDelegate.
//
// It handles:
//   "door_opened"
//   "motion_detected"
//
// For "door_opened":
//   [Security] Door opened by <deviceName>
//
// For "motion_detected":
//   [Security] Motion detected by <deviceName>
//
// For anything else:
//   [Security] Ignored event: <event>
//
// Override handleEvent().
class SecurityDelegate: public EventDelegate {
public:
  void handleEvent(const SmartEvent& event) const override {
    const std::string event_name = event.getEvent();
    if(event_name == "door_opened") {
      std::cout <<"[Security] Door opened by " << event.getDeviceName() <<"\n";
    } else if(event_name == "motion_detected") {
      std::cout <<"[Security] Motion detected by " << event.getDeviceName() <<"\n";
    } else {
      std::cout <<"[Security] Ignored event: " << event_name <<"\n";
    }
  }
};


// TODO 4:
// Create ComfortDelegate.
//
// It should inherit from EventDelegate.
//
// It handles:
//   "temperature_high"
//
// Output:
//   [Comfort] High temperature detected: <value>C
//
// For anything else:
//   [Comfort] Ignored event: <event>
//
// Override handleEvent().
class ComfortDelegate: public EventDelegate {
public:
  void handleEvent(const SmartEvent& event) const override {
    const std::string event_name = event.getEvent();
    if(event_name == "temperature_high") {
      std::cout <<"[Comfort] High temperature detected: " << event.getValue() <<"C\n";
    } else {
      std::cout <<"[Comfort] Ignored event: " << event_name <<"\n";
    }
  }
};


// TODO 5:
// Create SmartHomeHub.
//
// It should:
//   - store a pointer to EventDelegate
//   - initially have no delegate
//
// It must provide:
//
//   void setDelegate(EventDelegate* delegate);
//
//   void receiveEvent(const SmartEvent& event);
//
// receiveEvent() should:
//   - delegate the event to the current delegate
//   - if no delegate exists, print:
//       [Hub] No delegate configured
//
// IMPORTANT:
// SmartHomeHub must NOT contain the actual security or
// temperature-handling logic. That responsibility belongs
// to the delegates.
class SmartHomeHub {
 EventDelegate* event_delegate_;
public:
  SmartHomeHub() : event_delegate_(nullptr) {}

  void setDelegate(EventDelegate* delegate) {
    event_delegate_ = delegate;
  }

  void receiveEvent(const SmartEvent& event) const {
    if(event_delegate_) {
      event_delegate_->handleEvent(event);
      return;
    }
    std::cout <<"[Hub] No delegate configured\n";
  }

};


// ============================================================
// DO NOT MODIFY main()
// ============================================================

int main() {

    SmartHomeHub hub;

    SmartEvent doorEvent(
        "Front Door",
        "door_opened",
        0
    );

    SmartEvent motionEvent(
        "Hallway Camera",
        "motion_detected",
        0
    );

    SmartEvent temperatureEvent(
        "Living Room Sensor",
        "temperature_high",
        32
    );

    // No delegate yet
    hub.receiveEvent(doorEvent);

    // Use SecurityDelegate
    SecurityDelegate security;

    hub.setDelegate(&security);

    hub.receiveEvent(doorEvent);
    hub.receiveEvent(motionEvent);
    hub.receiveEvent(temperatureEvent);

    // Switch delegate at runtime
    ComfortDelegate comfort;

    hub.setDelegate(&comfort);

    hub.receiveEvent(temperatureEvent);
    hub.receiveEvent(doorEvent);

    return 0;
}

/*
Expected output
[Hub] No delegate configured
[Security] Door opened by Front Door
[Security] Motion detected by Hallway Camera
[Security] Ignored event: temperature_high
[Comfort] High temperature detected: 32C
[Comfort] Ignored event: door_opened
*/