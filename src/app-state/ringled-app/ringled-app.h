#ifndef RINGLED_APP_H
#define RINGLED_APP_H

#include <Arduino.h>
#include <app-state/app-state.h>
#include <ring-led/ring-led.h>

class RingLedApp : public AppState {
private:
  const int CONNECTION_ATTEMPTS = 10;

public:
  RingLedApp(String ssid, String password, RingLed *ringLed);
};

#endif