#include "ManchesterRF.h"

int soundSensor = 2;
int LED = 3;
#define TX_PIN 4 //any pin can transmit

ManchesterRF rf(MAN_4800); //link speed, try also MAN_300, MAN_600, MAN_1200, MAN_2400, MAN_4800, MAN_9600, MAN_19200, MAN_38400

uint8_t data = 0;

void setup()
{
  pinMode (soundSensor, INPUT);
  pinMode (LED, OUTPUT);
  rf.TXInit(TX_PIN);
}

void loop()
{
  if (digitalRead(soundSensor))
    rf.transmitByte(1);
  digitalWrite(LED, digitalRead(soundSensor));
}
