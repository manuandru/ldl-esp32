#include "ring-led.h"
#include "ring-led-task.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define LED_BRIGHTNESS 100

RingLed::RingLed() {
  ring.begin();
  ring.setBrightness(LED_BRIGHTNESS);
  ring.show();
  xTaskCreate(ringLedStateTask, "RingLed", 10000, NULL, 1, NULL);
}

void RingLed::onStart() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = START;
  xSemaphoreGive(mutex);
}

void RingLed::onCredentialsMissing() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = CREDENTIALS_MISSING;
  xSemaphoreGive(mutex);
}

void RingLed::onSiteConnected() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = SITE_CONNECTED;
  xSemaphoreGive(mutex);
}

void RingLed::onCredentialsProvided() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = CREDENTIALS_PROVIDED;
  xSemaphoreGive(mutex);
}

void RingLed::onWifiError() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = WIFI_CONNECTION_ERROR;
  xSemaphoreGive(mutex);
}

void RingLed::onWifiConnected() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = WIFI_CONNECTION_SUCCESSFUL;
  xSemaphoreGive(mutex);
}