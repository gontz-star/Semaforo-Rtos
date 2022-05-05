#include <Arduino.h>

#include "TM1637Display.h"
#include "semaforo_task.h"
void taskDisplaySeg(void* pvParameters) {
  DEBUG_PRINTLN("DISPLAY");
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);
  extern LuzSemaforo semaforoEstado;
  extern Screens CurrentScreen;
  extern LuzSemaforo semaforoEstado;
  extern uint8_t redCount;
  extern uint8_t yellowCount;
  extern uint8_t greenCount;

  TM1637Display display(20, 21);
  display.setBrightness(0x0f);

  for (;;) {
    switch (CurrentScreen) {
      case Screens::Semaforo: {
        xLastWakeTime = xTaskGetTickCount();
        switch (semaforoEstado) {
          case LuzSemaforo::Rojo: {
            DEBUG_PRINTLN(redCount);
            display.showNumberDec(redCount--);
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
            break;
          }
          case LuzSemaforo::Amarillo: {
            DEBUG_PRINTLN(yellowCount);
            display.showNumberDec(yellowCount--);
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
            break;
          }
          case LuzSemaforo::Verde: {
            DEBUG_PRINTLN(greenCount);
            display.showNumberDec(greenCount--);
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
            break;
          }
        }

        break;
      }
      case Screens::Home: {
        break;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(15));
  }
}