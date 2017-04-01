#include <Arduino.h>
#include <U8g2lib.h>
#include "ManchesterRF.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SH1106_128X64_NONAME_4W_HW_SPI u8x8(/* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

#define RX_PIN 4 //any pin can receive
ManchesterRF rf(MAN_600);

uint8_t size;
uint8_t *data;
char num[3];

void setup(void) {
  Serial.begin(9600);
  u8x8.begin();
  u8x8.setPowerSave(0);
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
    }

    u8x8.drawString(0, 1, "TEMP: ");
    conNumToCharArr(data[0]);
    u8x8.draw2x2String(6, 1, num);
    u8x8.draw2x2String(10, 1, "'C");

    u8x8.drawString(0, 4, "VLAZ: ");
    conNumToCharArr(data[1]);
    u8x8.draw2x2String(6, 4, num);
    u8x8.draw2x2String(10, 4, "%");

    //    u8x8.setCursor(0, 1);
    //    u8x8.print("TEMP: ");
    //    u8x8.print(data[0]);
    //    u8x8.print("'C");
    //    u8x8.setCursor(0, 4);
    //    u8x8.print("VLAZ: ");
    //    u8x8.print(data[1]);
    //    u8x8.print("%");
    //    u8x8.refreshDisplay();
  }
}
void conNumToCharArr(int number) {
  String str = String(number);
  str.toCharArray(num, 3);
}
