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

  TM1637Display display(20, 21);
  display.setBrightness(0x0f);
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    switch (CurrentScreen) {
      case Screens::Semaforo: {
        switch (semaforoEstado) {
          case LuzSemaforo::Rojo: {
            static uint8_t red = 15;
            display.showNumberDec(red--);

            break;
          }
          case LuzSemaforo::Amarillo: {
            static uint8_t yellow = 10;
            display.showNumberDec(yellow--);

            break;
          }
          case LuzSemaforo::Verde: {
            static uint8_t green = 15;
            display.showNumberDec(green--);

            break;
          }
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        break;
      }
      case Screens::Home: {
        break;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(15));
  }
}