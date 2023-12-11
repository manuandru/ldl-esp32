#include "app-state/ap-webserver/ap-webserver.h"
#include "app-state/ringled-app.cpp"
#include <Arduino.h>
#include <Preferences.h>

AppState *appState;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }
  RingLed *ringLed = new RingLed();
  delay(1000);

  Preferences preferences;
  preferences.begin("wifi", false);
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");
  preferences.end();

  Serial.println("ssid: " + ssid);
  Serial.println("password: " + password);

  if (ssid.length() == 0 && password.length() == 0) {
    Serial.println("No WiFi credentials found.");
    appState = new APWebServer(ringLed);
  } else {
    ringLed->setCredentialsProvidedColor();
    Serial.println("WiFi credentials found.");
    appState = new RingLedApp(ssid, password);
  }
}

void loop() {}