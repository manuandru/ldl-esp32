#include "ringled-app.h"
#include "task/pressure-detection.h"
#include "util/connection-manager/connection-manager.h"
#include "util/pressure-handler/no-wifi-handler/no-wifi-handler.h"
#include "util/pressure-handler/normal-handler/normal-handler.h"
#include "util/pressure-handler/pressure-handler.h"
#include <Arduino.h>
#include <WiFi.h>

PressureHandler *pressureHandler;
ConnectionManager *connectionManager;

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
    ringLed->onConnectionError();
    pressureHandler = new NoWifiHandler(ringLed);
  } else {
    connectionManager = new ConnectionManager(ringLed);
    Serial.println("Connected to WiFi");
    pressureHandler = new NormalHandler(ringLed, connectionManager);
    xTaskCreate(
        [](void *pvParameters) {
          ConnectionManager *connectionManager =
              (ConnectionManager *)pvParameters;
          while (true) {
            connectionManager->loop();
            vTaskDelay(pdMS_TO_TICKS(1));
          }
        },
        "mqttHandlerTask", 4096, connectionManager, 1, NULL);
  }

  xTaskCreate(pressureDetectionTask, "pressureDetectionTask", 10000,
              pressureHandler, 1, NULL);
}
