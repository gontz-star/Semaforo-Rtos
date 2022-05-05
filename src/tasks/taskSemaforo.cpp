
#include "buttons/buttons.h"
#include "controllers/controllers.h"
#include "semaforo_task.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "touchscreen_config.h"
#include "views/views.h"
uint8_t redCount = 15;
uint8_t yellowCount = 10;
uint8_t greenCount = 15;
void taskSemaforo(void* pvParameters) {
  DEBUG_PRINTLN("STARTING SEMAFORO TASK");

  extern Screens CurrentScreen;
  extern Adafruit_TFTLCD tft;
  extern LuzSemaforo semaforoEstado;
  extern uint32_t contadorSemaforo;

  const uint16_t tiempoRojo = 15000;
  const uint16_t tiempoAmarillo = 10000;
  const uint16_t tiempoVerde = 15000;
  LuzSemaforo ultimoColor;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    // codigp
    switch (CurrentScreen) {
      case Screens::Semaforo: {
        switch (semaforoEstado) {
          case LuzSemaforo::Rojo: {
            DEBUG_PRINT("millis =  ");
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tiempoRojo));
            ultimoColor = LuzSemaforo::Rojo;
            semaforoEstado = LuzSemaforo::Amarillo;
            viewSemaforo(&tft, buttonsSemaforo);
            DEBUG_PRINTLN("amairlol");
            yellowCount = 10;
            break;
          }
          case LuzSemaforo::Amarillo: {
            // amarinllol
            DEBUG_PRINT("millis =  ");
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tiempoAmarillo));

            if (ultimoColor == LuzSemaforo::Rojo) {
              semaforoEstado = LuzSemaforo::Verde;
            } else {
              semaforoEstado = LuzSemaforo::Rojo;
            }
            ultimoColor = LuzSemaforo::Amarillo;

            viewSemaforo(&tft, buttonsSemaforo);
            break;
          }
          case LuzSemaforo::Verde: {
            // verdib
            DEBUG_PRINT("millis =  ");
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tiempoVerde));
            ultimoColor = LuzSemaforo::Verde;
            semaforoEstado = LuzSemaforo::Amarillo;
            viewSemaforo(&tft, buttonsSemaforo);
            DEBUG_PRINTLN("amairlol");
            yellowCount = 10;
            break;
          }
        }

        // contadorSemaforo = millis();

        break;
      }

      case Screens::Home: {
        break;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}