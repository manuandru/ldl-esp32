#ifndef NORMAL_HANDLER_H
#define NORMAL_HANDLER_H

#include "../../connection-manager/connection-manager.h"
#include "../pressure-handler.h"

class NormalHandler : public PressureHandler {
private:
  ConnectionManager *connectionManager;

protected:
  RingLed *ringLed;
  void onStart();
  void onUpdate(int difference);
  void onShortPress();
  void onMiddlePress();

public:
  NormalHandler(RingLed *ringLed, ConnectionManager *connectionManager);
};

#endif