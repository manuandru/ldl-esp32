#include "ringled-app.h"
#include <Arduino.h>
#include <WiFi.h>

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
    return;
  }

  Serial.println("Connected to WiFi");
}
