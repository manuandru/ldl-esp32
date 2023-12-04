#include "ap-webserver.cpp"
#include "ringled-app.cpp"
#include <Arduino.h>
#include <Preferences.h>

AppState *appState;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  delay(1000);

  Preferences preferences;
  preferences.begin("wifi", false);
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");
  preferences.end();

  Serial.println("ssid: " + ssid);
  Serial.println("password: " + password);

  // if (ssid.length() == 0 || password.length() == 0) {
  // Serial.println("No WiFi credentials found.");
  // appState = new APWebServer();
  // } else {
  Serial.println("WiFi credentials found.");
  appState = new RingLedApp(ssid, password);
  // }

  appState->setup();
}

void loop() { appState->loop(); }