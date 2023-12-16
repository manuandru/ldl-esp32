#include "pressure-detection.h"
#include "config.h"
#include <Arduino.h>
#include <app-state/ringled-app/util/pressure-handler.h>

void pressureDetectionTask(void *parameter) {
  PressureHandler *handler = (PressureHandler *)parameter;
  while (true) {
    if (touchRead(PRESSURE_DETECTION_PIN) < PRESSURE_DETECTION_THRESHOLD) {
      handler->onInteractionStart();
      // Serial.println("Touch: " + String(touchRead(PRESSURE_DETECTION_PIN)));
      while (touchRead(PRESSURE_DETECTION_PIN) < PRESSURE_DETECTION_THRESHOLD) {
        handler->onInteractionUpdate();
        vTaskDelay(pdMS_TO_TICKS(25));
      }
      handler->onInteractionEnd();
    }
    vTaskDelay(pdMS_TO_TICKS(25));
  }
}
