#include "DEBUG_things.h"
#include "buttons/buttons.h"
#include "common_defs.h"
#include "controllers/controllers.h"
#include "semaforo_task.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "src/TouchScreen.h"
#include "touchscreen_config.h"
#include "views/views.h"
Screens CurrentScreen;
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void taskTouchscreenMenu(void* pvParameters) {
  DEBUG_PRINTLN("STARTING TOUCHSCREEN TASK");

  TouchScreen ts = TouchScreen(XP, YP, XM, YM, RX);

  uint16_t lcd_id = tft.readID();
  uint8_t lcd_rotation = 0;

  switch (lcd_id) {
    case 0x9325: {
      lcd_rotation = 1;
      break;
    }
    case 0x9341: {
      lcd_rotation = 3;
      break;
    }
    case 0xC0C0: {  // 0x9341
      DEBUG_PRINT(F("UNRECOGNIZED DRIVER (0x"));
      DEBUG_PRINTHEX(lcd_id);
      DEBUG_PRINTLN(F(") USING 0x9341 DRIVER"));
      lcd_id = 0x9341;
      lcd_rotation = 3;
      break;
    }
    default: {
      DEBUG_PRINT(F("UNRECOGNIZED DRIVER (0x"));
      DEBUG_PRINTHEX(lcd_id);
      DEBUG_PRINTLN(F(") USING 0x9341 DRIVER"));
      lcd_id = 0x9341;
      lcd_rotation = 3;
      break;
    }
  }
  DEBUG_PRINT(F("LCD driver reported by screen: 0x"));
  DEBUG_PRINTLNHEX(lcd_id);
  DEBUG_PRINT(F("TFT size is "));
  DEBUG_PRINT(tft.width());
  DEBUG_PRINT(F("x"));
  DEBUG_PRINTLN(tft.height());

  tft.reset();
  tft.begin(lcd_id);
  tft.setRotation(lcd_rotation);

  tft.fillScreen(BLACK);
  CurrentScreen = Screens::Home;
  viewHome(&tft, buttonsHome);

  for (;;) {
    taskENTER_CRITICAL();
    TSPoint p = ts.getPoint();

    // si quiero dibujar la pantalla sin tocar la ts, después de llamar
    // .getpoint() hay que arreglar la direccion de los pines, ya que los
    // comparten
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    taskEXIT_CRITICAL();
    if (p.z > MINPRESSURE) {
      // el modulo tactil tiene 60 puntos no dibujables en la pantalla
      TSPoint pointTmp = p;

      p.y = map(pointTmp.x, TS_MINX, TS_MAXX, tft.height(), 0);
      p.x = map(pointTmp.y, TS_MINY, TS_MAXY - 60, 0, tft.width());

      switch (CurrentScreen) {
        case Screens::Home: {
          controllerHome(&tft, buttonsHome, buttonsSemaforo, p);
          break;
        }
        case Screens::Semaforo: {
          controllerSemaforo(&tft, buttonsSemaforo, buttonsHome, p);
          break;
        }

        default: {
          break;
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(15));
  }
}