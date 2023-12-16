#include "no-wifi-handler.h"

NoWifiHandler::NoWifiHandler(RingLed *ringLed) { this->ringLed = ringLed; };

void NoWifiHandler::onStart() {
  // Nothing to do here
}

void NoWifiHandler::onUpdate(int difference) {
  float progress = float(difference) / float(LONG_PRESS_MILLIS);
  this->ringLed->onInteractionUpdate(progress);
}

void NoWifiHandler::onShortPress() { this->ringLed->onWifiError(); }

void NoWifiHandler::onMiddlePress() { this->onShortPress(); }