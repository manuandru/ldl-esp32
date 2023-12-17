#ifndef PRESSURE_HANDLER_H
#define PRESSURE_HANDLER_H

#include <Arduino.h>
#include <Preferences.h>
#include <ring-led/ring-led.h>

#define LONG_PRESS_MILLIS 6000
#define NO_UPDATE_STATE_THRESHOLD 1000
#define SHORT_PRESS_MILLIS 50

class PressureHandler {
private:
  unsigned long start = 0;

protected:
  RingLed *ringLed;
  virtual void onStart() = 0;
  virtual void onUpdate(int difference);
  virtual void onShortPress();
  virtual void onMiddlePress();
  void onLongPress() {
    this->ringLed->onPasswordReset();

    Preferences preferences;
    preferences.begin("wifi", false);
    preferences.remove("ssid");
    preferences.remove("password");
    preferences.end();

    delay(2000);
    ESP.restart();
  }

public:
  void onInteractionStart() {
    start = millis();
    onStart();
  }
  void onInteractionUpdate() { this->onUpdate(millis() - start); }
  void onInteractionEnd() {
    int difference = millis() - start;
    if (difference > LONG_PRESS_MILLIS) {
      onLongPress();
    } else if (difference > SHORT_PRESS_MILLIS &&
               difference < NO_UPDATE_STATE_THRESHOLD) {
      onShortPress();
    } else {
      this->onMiddlePress();
    }
  }
};

#endif
