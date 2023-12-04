#include "app-state.h"
#include <Arduino.h>
#include <WiFi.h>

#define LED_BUILTIN 2

class RingLedApp : public AppState {

private:
  String ssid;
  String password;
  const int CONNECTION_ATTEMPTS = 3;

public:
  RingLedApp(String ssid, String password) {
    this->ssid = ssid;
    this->password = password;

    Serial.println("Costruttore");
    Serial.println(this->ssid);
    Serial.println(this->password);
  };

  void setup() {

    Serial.println("Setup");
    Serial.println(this->ssid);
    Serial.println(this->password);

    WiFi.begin(this->ssid.c_str(), this->password.c_str());

    for (int i = 0; i < CONNECTION_ATTEMPTS; i++) {
      if (WiFi.status() == WL_CONNECTED) {
        break;
      }
      delay(1000);
      Serial.println("Connecting to WiFi... Attempt " + String(i));
    }

    if (WiFi.status() != WL_CONNECTED) {
      // Set the internal LED to red
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Failed to connect to WiFi");
      return;
    }

    Serial.println("Connected to WiFi");
  }

  void loop() {
    Serial.println("RingLedApp loop");
    delay(1000);
  }
};
