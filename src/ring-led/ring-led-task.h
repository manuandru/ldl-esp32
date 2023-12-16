#ifndef RING_LED_TASK
#define RING_LED_TASK

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <freertos/FreeRTOS.h>

enum RingLedState {
  START,
  CREDENTIALS_MISSING,
  SITE_CONNECTED,
  CREDENTIALS_PROVIDED,
  WIFI_CONNECTION_ERROR,
  WIFI_CONNECTION_SUCCESSFUL
};
extern SemaphoreHandle_t mutex;
extern Adafruit_NeoPixel ring;
extern RingLedState state;

void ringLedStateTask(void *parameter);

#endif