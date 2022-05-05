#include "buttons/buttonsSemaforo.h"
#include "views/views.h"
extern LuzSemaforo semaforoEstado;

void viewSemaforo(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsSemaforo) {
  DEBUG_PRINTLN("dibujando semaforo");

  tft->setCursor(0, 0);
  tft->setTextSize(3);
  tft->setTextColor(WHITE, BLACK);
  switch (semaforoEstado) {
    case LuzSemaforo::Rojo: {
      // rjoo
      // prender pantalla rojo.
      tft->fillScreen(RED);
      tft->print("ROJO");
      DEBUG_PRINTLN("DIBUJANDO ROJO");
      break;
    }
    case LuzSemaforo::Amarillo: {
      // amarinllol
      tft->fillScreen(YELLOW);
      tft->print("AMARILLO");
      DEBUG_PRINTLN("DIBUJANDO AMARILLO");
      break;
    }
    case LuzSemaforo::Verde: {
      // verdib
      tft->fillScreen(GREEN);
      tft->print("VERDE");
      DEBUG_PRINTLN("DIBUJANDO VERDE");
      break;
    }
  }

  /*
  tft->fillCircle(50,50,10,RED);
  tft->fillCircle(100,30,10,BLUE);
  tft->fillCircle(10,100,10,YELLOW);
  */

  buttonsSemaforo[BUTTON_SCREEN_BACK].initButtonUL(tft,0,150,220,40,WHITE,BLACK,WHITE,"BACK",3);
  buttonsSemaforo[BUTTON_SCREEN_BACK].drawButton();

}