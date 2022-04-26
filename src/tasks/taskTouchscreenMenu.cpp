#include "DEBUG_things.h"
#include "common_defs.h"
#include "controllers/controllers.h"
#include "semaforo_task.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "src/TouchScreen.h"
#include "touchscreen_config.h"
#include "views/views.h"

Screens CurrentScreen;
void taskTouchscreenMenu(void* pvParameters) {
  Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

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
}