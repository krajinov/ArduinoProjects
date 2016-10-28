#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
//Connect RF-Transmitter to pin 12 on your ArduinoUNO

RH_ASK driver;

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
