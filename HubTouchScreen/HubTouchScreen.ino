#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include <EEPROM.h>
#include <TouchScreen.h>


// color choices add more when needed
#define BLACK 0x0000
#define BLUE 0x001F
#define GREEN 0x07E0
#define RED 0xF800
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define YELLOW 0xFFE0


MCUFRIEND_kbv tft;  //(A3, A2, A1, A0, A4)

// Calibration values obtained from TouchScreen_Calibr_native(file->examples->MCUFRIEND_kbv->TouchScreen_Calibr_native.ino)
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
const int XP = 6, XM = 16, YP = 15, YM = 7;  //240x320 ID=0x9595


// PORTRAIT  CALIBRATION     240 x 320
// x = map(p.x, LEFT = 889, RT = 149, 0, 240)
// y = map(p.y, TOP = 97, BOT = 893, 0, 320)

// LANDSCAPE CALIBRATION     320 x 240
// x = map(p.y, LEFT = 97, RT = 893, 0, 320)
// y = map(p.x, TOP = 149, BOT = 889, 0, 240)

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);

TSPoint tp;
#define MINPRESS 10
#define MAXPRESS 1000
bool checkButtonPressed(uint16_t touch_x, uint16_t touch_y, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  if (touch_x >= x && touch_x <= x + width && touch_y >= y && touch_y <= y + height) {
    return true;
  }
  return false;
}
void setup() {
  tft.reset();
  Serial.begin(115200);

  // begin touch screen intiate
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
}

void loop() {
  uint16_t touch_x, touch_y;
  tp = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  digitalWrite(XM, HIGH);
  digitalWrite(YP, HIGH);
  tft.setRotation(0);

  // Check if the touchscreen is pressed
  if (tp.z >= MINPRESS && tp.z <= MAXPRESS) {
    touch_x = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
    touch_y = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
    //////////////// Debuging Switch on or off ////////////
    Serial.print("Touch X: ");
    Serial.print(touch_x);
    Serial.print("\tTouch Y: ");
    Serial.println(touch_y);
    //////////////////////////////////////////////////////
  tft.fillScreen(BLACK);

  }
}
