#include <Arduino.h>
#include <U8g2lib.h>
#include "ManchesterRF.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SH1106_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

#define RX_PIN 4 //any pin can receive
ManchesterRF rf(MAN_1200);

const uint8_t arrSize = 3;
uint8_t size;
int8_t *data;
uint8_t moveTxt = 0;
boolean revMov = false;
char num[arrSize];

const uint8_t TILE_DEGR[8] =
{ B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000110,
  B00001001,
  B00001001,
  B00000110
};
const byte THERMOMETER[2][8] =
{
  { B00000000,
    B11111100,
    B00000010,
    B00000001,
    B01010001,
    B01010010,
    B11111100,
    B00000000
  },
  { B00111000,
    B01000111,
    B10110000,
    B10111000,
    B10111101,
    B10110101,
    B01000111,
    B00111000
  }
};
const int THERMOMETER_LEN = sizeof(THERMOMETER) / 8;

const byte HUM[2][8] =
{
  { B00011100,
    B00100010,
    B00100001,
    B10100010,
    B01011100,
    B00100000,
    B01000000,
    B10000000
  },
  { B00000000,
    B00000000,
    B00000000,
    B00000011,
    B00000100,
    B00000100,
    B00000100,
    B00000011
  }
};
const int HUM_LEN = sizeof(HUM) / 8;

void setup(void) {
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setContrast(100);
  u8x8.setFont(u8x8_font_pxplusibmcgathin_u);
  rf.RXInit(RX_PIN);
}

void loop(void) {
  if (rf.available()) { //something is in RX buffer
    if (rf.receiveArray(size, &data)) {
      //process the data
      for (int i = 0; i < size; i++) {
        Serial.println(data[i]); //do something with the data
      }
      u8x8.clear();

      //Draw temperature
      drawTemp(data[0]);

      //Draw humidity
      drawHum(data[1]);

      moveColsCursor();
    }
  }
}

void convNumToCharArr(int number) {
  String str = String(number);
  str.toCharArray(num, arrSize);
}

void drawTemp(int8_t temp) {
  // Draw thermometer
  for (int i = 0; i < THERMOMETER_LEN; i++) {
    u8x8.drawTile(moveTxt + 0, i + 1, 1, THERMOMETER[i]);
  }
  uint8_t shiftPos = (temp >= 0 && temp < 10) ? 0 : 1;
  
  // Convert temperature integer to char array
  convNumToCharArr(data[0]);
  // Draw temp string
  u8x8.draw2x2String(moveTxt + 2, 1, num);
  u8x8.drawTile(moveTxt + 5 + shiftPos, 1, 1, TILE_DEGR);
  u8x8.draw2x2String(moveTxt + 6 + shiftPos, 1, "C");
}

void drawHum(int8_t hum) {
  // Draw moisture custom char
  for (int i = 0; i < HUM_LEN; i++) {
    u8x8.drawTile(7 - moveTxt, i + 5, 1, HUM[i]);
  }
  // Convert humidity integer to char array
  convNumToCharArr(data[1]);
  // Draw humidity string
  u8x8.draw2x2String(9 - moveTxt, 5, num);
  u8x8.draw2x2String(14 - moveTxt, 5, "%");
}

void moveColsCursor() {
  if (moveTxt == 7) revMov = true;
  else if (moveTxt == 0) revMov = false;

  if (moveTxt >= 0 && moveTxt < 7 && !revMov) {
    moveTxt ++;
  }
  else {
    moveTxt--;
  }
}
