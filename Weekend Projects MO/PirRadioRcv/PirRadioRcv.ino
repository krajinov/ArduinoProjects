#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
// Connect RF-Receiver on pin 11 on your Arduino uno

RH_ASK driver;
int piezo = 7;
String alert = "Motion Detected!";

void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init()){
         Serial.println("init failed");
         }
    pinMode(piezo, OUTPUT);
}

void loop()
{
    uint8_t buf[16];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      String s =  String((char*)buf).substring(0, 16);
      // Message with a good checksum received, dump it.
      if(s.equals(alert)){
        for (int i=0; i<500; i++) {  // generate a XKHz tone for 1/2 second
          digitalWrite(piezo, HIGH);
          delayMicroseconds(100);
          digitalWrite(piezo, LOW);
          delayMicroseconds(300);
          }
          delay(2000);
        }

      Serial.println("Message: " + s);
    }
}
