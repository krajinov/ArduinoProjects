#include <TimeLib.h>
#include <DS3232RTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RF24.h"
#include <SPI.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);           

int msg[1];                                       //Request message holder

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 */
RF24 radio(9, 10);

/*Pipes for reading/writing respectively*/
uint8_t addresses[][6] = {"1Node", "2Node"};
/*Set channel above WiFi band.*/
uint8_t channel = 124;
/*Set response timeout period*/
unsigned long timeout_period = 200000;


uint8_t PINWEATH = 3;                         //Switch for sending DHT sensor data request
boolean dataSend = false;                     //If request was sent, set this to true

struct weather {
  float temp;
  float hum;
};

typedef struct weather Weather;
Weather data;


/**
   Byte arrays for creating custom LCD chars
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
  Serial.begin(9600);
  Serial.println("...initializing");
  pinMode(PINWEATH, INPUT);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(channel);
  radio.openReadingPipe(1, addresses[0]);
  radio.openWritingPipe(addresses[1]);
  radio.powerDown();

  lcd.init();                      // initialize the lcd
  lcd.backlight();
  //Creating custom chars
  lcd.createChar(1, heart);
  lcd.createChar(2, degree);
  
  // Print a message to the LCD.
  lcd.setCursor(5, 0);
  lcd.print("Arduino");
  lcd.setCursor(2, 1);
  lcd.write(1);
  lcd.print("Ivy Clock");
  lcd.write(1);
  delay(2000);
  setSyncProvider(RTC.get);   // the function (from TimeLib.h) to get the time from the RTC
  lcd.clear();
  if (timeStatus() != timeSet) {
    lcd.setCursor(0, 0);
    lcd.print("Unable to sync");
    lcd.setCursor(0, 1);
    lcd.print("with the RTC");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("RTC has set");
    lcd.setCursor(0, 1);
    lcd.print("the system time");
  }
  delay(1500);
  lcd.clear();
  Serial.println("System online!");
}


void loop() {
  if (digitalRead(PINWEATH) == HIGH) {
    Serial.println("Button high!");
    radio.powerUp();
    delay(20);
    if (!dataSend) {
      Serial.println("Data Send");
      msg[0] = 111;
      if (!radio.write(msg, 1)) {
        Serial.println("failed");
      } else {
        dataSend = true;
        radio.startListening();
        radioListen();
      }
    }

  } else {
    dataSend = false;
    digitalClockDisplay();
  }
}

void digitalClockDisplay(void)
{
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  printHours(hour());
  printDigits(minute());
  printDigits(second());
  lcd.setCursor(0, 1);
  float c = RTC.temperature() / 4.;
  lcd.print("Temp: ");
  lcd.print(c);
  lcd.write(2);
  lcd.print("C");
}

void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(':');
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

void printHours(int hours)
{
  // utility function for digital clock display
  if (hours < 10)
    lcd.print('0');
  lcd.print(hours);
}

void printDHT() {
  lcd.clear();                                              // Clear display for displaying sensor data
  lcd.print("Temp: ");
  lcd.print(data.temp, 1);                                  // Print recieved DHT temperature
  lcd.write(2);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(data.hum, 1);                                   // Print recieved DHT humidity
  lcd.print(" %");
  delay(4000);
  dataSend = false;
  lcd.clear();
}

void radioListen() {
  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

  while (! radio.available() ) {                            // While nothing is received
    if (micros() - started_waiting_at > timeout_period ) {  // If waited longer than timeout period, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }
  if ( timeout ) {                                          // Describe the results
    radio.stopListening();                                  //Stop listening and power down the radio
    radio.powerDown();
    Serial.println("Failed, response timed out.");
  } else {
    while (radio.available()) {
      radio.read(&data, sizeof(data));
      radio.stopListening();
      radio.powerDown();
      delay(30);
      Serial.println("Data Rec");
      printDHT();
    }
  }
}
