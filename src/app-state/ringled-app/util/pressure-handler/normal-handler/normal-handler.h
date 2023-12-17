#ifndef NORMAL_HANDLER_H
#define NORMAL_HANDLER_H

#include "../pressure-handler.h"

class NormalHandler : public PressureHandler {
protected:
  RingLed *ringLed;
  void onStart();
  void onUpdate(int difference);
  void onShortPress();
  void onMiddlePress();

public:
  NormalHandler(RingLed *ringLed);
};

#endif