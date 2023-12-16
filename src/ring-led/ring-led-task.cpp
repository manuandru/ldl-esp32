#include "ring-led-task.h"
#include "freertos/FreeRTOS.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define LED_PIN 25
#define LED_COUNT 12

Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
RingLedState state = START;
float interactionProgress = 0.0;

void colorWipe(uint32_t color, int wait);
void reverseColorWipe(uint32_t color, int wait);
void theaterChase(uint32_t color, int wait);
void rainbow(int wait);
void theaterChaseRainbow(int wait);
void fading(uint8_t r, uint8_t g, uint8_t b, int wait);
void backFading(uint8_t r, uint8_t g, uint8_t b, int wait);

void ringLedStateTask(void *parameter) {
  while (1) {
    xSemaphoreTake(mutex, portMAX_DELAY); // Take the mutex
    RingLedState currentState = state;
    xSemaphoreGive(mutex); // Release the mutex

    switch (currentState) {
    case START:
      ring.clear();
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(100));
      break;
    case CREDENTIALS_MISSING:
      colorWipe(ring.Color(255, 50, 0), 100);
      colorWipe(ring.Color(0, 0, 0), 50);
      break;
    case SITE_CONNECTED:
      fading(255, 50, 0, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      backFading(255, 50, 0, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      break;
    case CREDENTIALS_PROVIDED:
      // fade with light blue
      fading(0, 200, 255, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      backFading(0, 200, 255, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      break;
    case WIFI_CONNECTION_ERROR:
      // fade with red
      fading(255, 0, 0, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      backFading(255, 0, 0, 2);
      vTaskDelay(pdMS_TO_TICKS(100));
      break;
    case WIFI_CONNECTION_SUCCESSFUL:
      // fade with green
      fading(0, 255, 0, 1);
      vTaskDelay(pdMS_TO_TICKS(50));
      backFading(0, 255, 0, 1);
      vTaskDelay(pdMS_TO_TICKS(50));
      break;
    case WAITING_FOR_INTERACTION:
      ring.clear();
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(25));
      break;
    case INTERACTION_START:
      ring.clear();
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(25));
      break;
    case INTERACTION_UPDATE:
      ring.clear();
      for (int i = 0; i < ring.numPixels() * interactionProgress; i++) {
        ring.setPixelColor(i, ring.Color(255, 50, 0));
      }
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(5));
      break;
    case MESSAGE_SENT:
      // Blink with green
      theaterChase(ring.Color(0, 255, 0), 50);
      xSemaphoreTake(mutex, portMAX_DELAY);
      state = WAITING_FOR_INTERACTION;
      xSemaphoreGive(mutex);
      break;
    case PASSWORD_RESET:
      // Blink with red
      theaterChase(ring.Color(255, 0, 0), 100);
      xSemaphoreTake(mutex, portMAX_DELAY);
      state = WAITING_FOR_INTERACTION;
      xSemaphoreGive(mutex);
      break;
    }

    // Serial.println("Counter: " + String(counter++));
    // colorWipe(ring.Color(255, 0, 0), 50);
    // reverseColorWipe(ring.Color(0, 255, 0), 50);
    // theaterChase(ring.Color(0, 0, 255), 50);
    // rainbow(20);
    // theaterChaseRainbow(50);
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
    ring.show();
    vTaskDelay(pdMS_TO_TICKS(wait));
  }
}

void reverseColorWipe(uint32_t color, int wait) {
  for (int i = ring.numPixels() - 1; i > 0; i--) {
    ring.setPixelColor(i, color);
    ring.show();
    vTaskDelay(pdMS_TO_TICKS(wait));
  }
}

uint8_t scaleTo256(uint8_t value, uint8_t scale) { return value * scale / 256; }

void fading(uint8_t r, uint8_t g, uint8_t b, int wait) {
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < ring.numPixels(); j++) {
      ring.setPixelColor(
          j, ring.Color(scaleTo256(r, i), scaleTo256(g, i), scaleTo256(b, i)));
    }
    ring.show();
    vTaskDelay(pdMS_TO_TICKS(wait));
  }
}

void backFading(uint8_t r, uint8_t g, uint8_t b, int wait) {
  for (int i = 255; i >= 0; i--) {
    for (int j = 0; j < ring.numPixels(); j++) {
      ring.setPixelColor(
          j, ring.Color(scaleTo256(r, i), scaleTo256(g, i), scaleTo256(b, i)));
    }
    ring.show();
    vTaskDelay(pdMS_TO_TICKS(wait));
  }
}

void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 3; b++) {
      ring.clear();
      for (int c = b; c < ring.numPixels(); c += 3) {
        ring.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(wait));
    }
  }
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536;
       firstPixelHue += 256) {
    for (int i = 0; i < ring.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / ring.numPixels());
      ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue)));
    }
    ring.show();
    vTaskDelay(pdMS_TO_TICKS(wait));
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0; // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) {
      ring.clear();
      for (int c = b; c < ring.numPixels(); c += 3) {
        int hue = firstPixelHue + c * 65536L / ring.numPixels();
        uint32_t color = ring.gamma32(ring.ColorHSV(hue));
        ring.setPixelColor(c, color);
      }
      ring.show();
      vTaskDelay(pdMS_TO_TICKS(wait));
      firstPixelHue += 65536 / 90;
    }
  }
}
