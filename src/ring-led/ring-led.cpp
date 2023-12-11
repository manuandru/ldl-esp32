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

void RingLed::setCredentialsMissingColor() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = CREDENTIALS_MISSING;
  xSemaphoreGive(mutex);
}

void RingLed::setSiteConnectedColor() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = SITE_CONNECTED;
  xSemaphoreGive(mutex);
}

void RingLed::setCredentialsProvidedColor() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = CREDENTIALS_PROVIDED;
  xSemaphoreGive(mutex);
}