#include "normal-handler.h"

NormalHandler::NormalHandler(RingLed *ringLed) { this->ringLed = ringLed; };

void NormalHandler::onStart() { this->ringLed->onInteractionStart(); }

void NormalHandler::onUpdate(int difference) {
  if (difference > NO_UPDATE_STATE_THRESHOLD) {
    float progress = float(difference - NO_UPDATE_STATE_THRESHOLD) /
                     float(LONG_PRESS_MILLIS - NO_UPDATE_STATE_THRESHOLD);
    this->ringLed->onInteractionUpdate(progress);
  }
}

void NormalHandler::onShortPress() { this->ringLed->onMessageSent(); }

void NormalHandler::onMiddlePress() {
  this->ringLed->onWaitingForInteraction();
}