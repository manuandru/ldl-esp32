#include "ringled-app.h"
#include "task/pressure-detection.h"
#include "util/pressure-handler/no-wifi-handler/no-wifi-handler.h"
#include "util/pressure-handler/normal-handler/normal-handler.h"
#include "util/pressure-handler/pressure-handler.h"
#include <Arduino.h>
#include <WiFi.h>

PressureHandler *pressureHandler;

RingLedApp::RingLedApp(String ssid, String password, RingLed *ringLed) {

  WiFi.begin(ssid.c_str(), password.c_str());
  for (int i = 0; i < CONNECTION_ATTEMPTS; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    delay(1000);
    Serial.println("Connecting to WiFi... Attempt " + String(i));
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    ringLed->onWifiError();
    pressureHandler = new NoWifiHandler(ringLed);
  } else {
    Serial.println("Connected to WiFi");
    ringLed->onWifiConnected();
    pressureHandler = new NormalHandler(ringLed);
    delay(2000);
    ringLed->onWaitingForInteraction();
  }

  xTaskCreate(pressureDetectionTask, "pressureDetectionTask", 10000,
              pressureHandler, 1, NULL);
}
