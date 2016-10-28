#include <TimeLib.h>
#include <DS3232RTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/**
 * Byte arrays for creating custom chars
 */
byte heart[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00000
};

byte degree[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.setBacklight(10);
  //Creating custom chars
  lcd.createChar(1, heart);
  lcd.createChar(2, degree);
  // Print a message to the LCD.
  lcd.setCursor(5,0);
  lcd.print("Arduino");
  lcd.setCursor(2,1);
  lcd.write(1);
  lcd.print("Ivy Clock");
  lcd.write(1);
  delay(2000);
  setSyncProvider(RTC.get);   // the function (from TimeLib.h) to get the time from the RTC
  lcd.clear();
  if(timeStatus() != timeSet){
    lcd.setCursor(0,0);
    lcd.print("Unable to sync");
    lcd.setCursor(0,1);
    lcd.print("with the RTC");
    } else {
      lcd.setCursor(0,0);
      lcd.print("RTC has set");
      lcd.setCursor(0,1);
      lcd.print("the system time");
      }
  delay(1500);
  lcd.clear();
}


void loop(){
  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay(void)
{
    lcd.setCursor(0,0);
    lcd.print("Time: ");
    lcd.print(hour());
    printDigits(minute());
    printDigits(second());
    lcd.setCursor(0,1);
    float c = RTC.temperature() / 4.;
    lcd.print("Temp: ");
    lcd.print(c);
    lcd.write(2);
    lcd.print("C");
//    lcd.print("\337C");
//    lcd.write(B11011111);
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    lcd.print(':');
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}
