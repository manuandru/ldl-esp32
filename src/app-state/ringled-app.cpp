#include "app-state.h"
#include <Arduino.h>
#include <WiFi.h>

#define LED_BUILTIN 2

class RingLedApp : public AppState {

private:
  String ssid;
  String password;
  const int CONNECTION_ATTEMPTS = 3;
  bool wifiConnection;

public:
  RingLedApp(String ssid, String password) {
    this->ssid = ssid;
    this->password = password;
  };

  void setup() {

    WiFi.begin(this->ssid.c_str(), this->password.c_str());
    for (int i = 0; i < CONNECTION_ATTEMPTS; i++) {
      if (WiFi.status() == WL_CONNECTED) {
        break;
      }
      delay(1000);
      Serial.println("Connecting to WiFi... Attempt " + String(i));
    }

    pinMode(LED_BUILTIN, OUTPUT);

    if (WiFi.status() != WL_CONNECTED) {
      // Set the internal LED to red
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Failed to connect to WiFi");
      return;
    }

    wifiConnection = true;

    Serial.println("Connected to WiFi");
  }

  void loop() {
    Serial.println("RingLedApp loop");

    if (wifiConnection) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    } else {
      delay(1000);
    }
  }
};
