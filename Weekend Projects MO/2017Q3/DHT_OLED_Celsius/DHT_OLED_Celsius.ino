#include <U8g2lib.h> // U8glib library
#include <dht.h>     // DHT library

#define dht_apin 3  // Analog pin to which the sensor is connected
dht DHT;
/*Uncomment and comment*/
U8G2_SH1106_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void draw()
{
  u8g2.drawStr(0, 20, "Temp: ");   // put string of display at position X, Y
  u8g2.drawStr(0, 60, "Hum: ");
  u8g2.setCursor(72, 20);        // set position
  u8g2.print(DHT.temperature, 0);  // display temperature from DHT11 in Celsius
  u8g2.println("°C");
  u8g2.setCursor(72, 60);        // set position
  u8g2.print(DHT.humidity, 0);     // display humidity from DHT11
  u8g2.println("%");
}
void setup()
{
  u8g2.begin(); 
  u8g2.setContrast(7);
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_profont22_tf);   // select font
}

void loop()
{
  DHT.read22(dht_apin);  // Read apin on DHT11
  u8g2.firstPage();
  do
  {
    draw();
  }  while ( u8g2.nextPage() );
  delay(2000);  // Delay of 2 sec before accessing DHT11 (min - 2sec)
}
/*END OF FILE*/
