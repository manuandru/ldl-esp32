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

void RingLed::onWaitingForInteraction() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = WAITING_FOR_INTERACTION;
  xSemaphoreGive(mutex);
}

void RingLed::onInteractionStart() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = INTERACTION_START;
  interactionProgress = 0.0;
  xSemaphoreGive(mutex);
}

void RingLed::onInteractionUpdate(float progress) {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = INTERACTION_UPDATE;
  interactionProgress = progress;
  xSemaphoreGive(mutex);
}

void RingLed::onMessageSent() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = MESSAGE_SENT;
  xSemaphoreGive(mutex);
}

void RingLed::onPasswordReset() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = PASSWORD_RESET;
  xSemaphoreGive(mutex);
}

void RingLed::onSomeoneElseInteracting() {
  xSemaphoreTake(mutex, portMAX_DELAY);
  state = SOMEONE_ELSE_INTERACTING;
  xSemaphoreGive(mutex);
}