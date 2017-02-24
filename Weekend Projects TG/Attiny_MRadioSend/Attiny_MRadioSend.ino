#include <Manchester.h>
/*
  Manchester Transmitter example
  In this example transmitter will send one 16 bit number
  per transmission.
  Try different speeds using these constants, your maximum
  possible speed will depend on various factors like transmitter 
  type, distance, microcontroller speed, ...
  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7
*/
  #define TX_PIN 7  //pin where your transmitter is connected
  uint16_t transmit_data = 2761;
  void setup() {
  man.setupTransmit(TX_PIN, MAN_1200);
} 
void loop() {
  man.transmit(transmit_data);
  delay(200);
}
