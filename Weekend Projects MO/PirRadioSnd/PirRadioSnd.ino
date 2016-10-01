#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
//Connect RF-Transmitter to pin 12 on your ArduinoUNO

RH_ASK driver;
int pirMS = 7;

int val = 0;

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init()){
         Serial.println("init failed");
    }
    pinMode(pirMS, INPUT);
}

void loop()
{
  val=digitalRead(pirMS);
    if(val == HIGH){
      sendMessage();
      } else {
        
      }
}

void sendMessage(){
    const char *msg = "Motion Detected!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(500);
  }
