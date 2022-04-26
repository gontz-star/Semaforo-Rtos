#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Adafruit_I2CDevice.h>
#include "DEBUG_things.h"
#include "SPI.h"
#include "common_defs.h"
#include "task.h"
#include "tasks/semaforo_task.h"

void setup() {
  // put your setup code here, to run once:
  DEBUG_BEGIN(9600);

  xTaskCreate(taskTouchscreenMenu, "Touchscreen_Menu",
              configMINIMAL_STACK_SIZE * 6, NULL, configMAX_PRIORITIES - 3,
              NULL);
              
  xTaskCreate(taskSemaforo, "Semaforo", configMINIMAL_STACK_SIZE, NULL,
              configMAX_PRIORITIES - 2, NULL);
}

void loop() {}