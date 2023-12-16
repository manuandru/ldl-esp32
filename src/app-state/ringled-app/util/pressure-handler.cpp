#include "pressure-handler.h"
#include <Arduino.h>
#include <Preferences.h>

PressureHandler::PressureHandler(RingLed *ringLed) { this->ringLed = ringLed; }

unsigned long start = 0;

void PressureHandler::onInteractionStart() {
  start = millis();
  this->ringLed->onInteractionStart();
}

void PressureHandler::onInteractionUpdate() {
  int difference = millis() - start;
  if (difference > NO_UPDATE_STATE_THRESHOLD) {
    float progress = float(difference - NO_UPDATE_STATE_THRESHOLD) /
                     float(LONG_PRESS_MILLIS - NO_UPDATE_STATE_THRESHOLD);
    this->ringLed->onInteractionUpdate(progress);
  }
}

void PressureHandler::onInteractionEnd() {
  int difference = millis() - start;
  if (difference > LONG_PRESS_MILLIS) {
    onLongPress();
  } else if (difference > SHORT_PRESS_MILLIS &&
             difference < NO_UPDATE_STATE_THRESHOLD) {
    onShortPress();
  } else {
    this->ringLed->onWaitingForInteraction();
  }
}

void PressureHandler::onShortPress() {
  ringLed->onMessageSent();
  // TODO: SEND TO SERVER
}

void PressureHandler::onLongPress() {
  ringLed->onPasswordReset();

  Preferences preferences;
  preferences.begin("wifi", false);
  preferences.remove("ssid");
  preferences.remove("password");
  preferences.end();

  delay(2000);
  ESP.restart();
}
