#ifndef PRESSURE_HANDLER_H
#define PRESSURE_HANDLER_H

#include <ring-led/ring-led.h>

#define LONG_PRESS_MILLIS 6000
#define NO_UPDATE_STATE_THRESHOLD 1000
#define SHORT_PRESS_MILLIS 50

class PressureHandler {
private:
  RingLed *ringLed;
  void onShortPress();
  void onLongPress();

public:
  PressureHandler(RingLed *ringLed);
  void onInteractionStart();
  void onInteractionUpdate();
  void onInteractionEnd();
};

#endif
