
#include "buttons/buttons.h"
#include "controllers/controllers.h"
#include "semaforo_task.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "touchscreen_config.h"
#include "views/views.h"
void taskSemaforo(void* pvParameters) {
  DEBUG_PRINTLN("STARTING SEMAFORO TASK");

  extern Screens CurrentScreen;
  extern Adafruit_TFTLCD tft;
  extern LuzSemaforo semaforoEstado;
  extern uint32_t contadorSemaforo;

  const uint16_t tiempoRojo = 15000;
  const uint16_t tiempoAmarillo = 10000;
  const uint16_t tiempoVerde = 15000;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    // codigp
    switch (CurrentScreen) {
      case Screens::Semaforo: {
        switch (semaforoEstado) {
          case LuzSemaforo::Rojo: {
            // rjoo
            // prender pantalla rojo.
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(tiempoRojo));
            semaforoEstado = LuzSemaforo::Amarillo;
            viewSemaforo(&tft, buttonsSemaforo);
            DEBUG_PRINTLN("amairlol");
            break;
          }
          case LuzSemaforo::Amarillo: {
            // amarinllol
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(tiempoAmarillo));
            semaforoEstado = LuzSemaforo::Verde;
            viewSemaforo(&tft, buttonsSemaforo);
            DEBUG_PRINTLN("verdre");
            break;
          }
          case LuzSemaforo::Verde: {
            // verdib
            DEBUG_PRINTLN(millis());
            vTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(tiempoVerde));
            semaforoEstado = LuzSemaforo::Rojo;
            viewSemaforo(&tft, buttonsSemaforo);
            DEBUG_PRINTLN("rojfooo");
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