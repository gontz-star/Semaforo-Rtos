#include "buttons/buttonsHome.h"
#include "controllers.h"
extern uint32_t contadorSemaforo;
extern LuzSemaforo semaforoEstado;
extern Screens CurrentScreen;
extern uint8_t redCount;

void controllerHome(Adafruit_TFTLCD *tft, Adafruit_GFX_Button *buttonsHome,
                    Adafruit_GFX_Button *buttonsSemaforo, const TSPoint p) {
  uint8_t pressedButton = 0xff;

  for (size_t i_btn = 0; i_btn < BUTTON_COUNT_HOME; i_btn++) {
    if (buttonsHome[i_btn].contains(p.x, p.y)) {
      pressedButton = i_btn;
      break;
    }
  }

  switch (pressedButton) {
    case BUTTON_SCREEN_SEMAFORO: {

      semaforoEstado = LuzSemaforo::Rojo;
      redCount = 15;
      CurrentScreen = Screens::Semaforo;
      viewSemaforo(tft, buttonsSemaforo);
      break;
    }

    default:
      break;
  }
}