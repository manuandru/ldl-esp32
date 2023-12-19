#ifndef NO_WIFI_HANDLER_H
#define NO_WIFI_HANDLER_H

#include "../pressure-handler.h"

class NoWifiHandler : public PressureHandler {
protected:
  void onStart();
  void onUpdate(int difference);
  void onShortPress();
  void onMiddlePress();

public:
  NoWifiHandler(RingLed *ringLed);
};

#endif
