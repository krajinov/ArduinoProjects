#include <ManchesterRF.h>
/*

  Manchester Receiver example
  
  In this example receiver will receive array of 10 bytes per transmittion

  try different speeds using this constants, your maximum possible speed will 
  depend on various factors like transmitter type, distance, microcontroller speed, ...

  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7

*/

#define TX_PIN 0
#define LED_PIN 1

 /*link speed, try also MAN_300, MAN_600, MAN_1200, 
   MAN_2400, MAN_4800, MAN_9600, MAN_19200, MAN_38400*/
ManchesterRF rf(MAN_1200);

uint8_t moo = 1;
#define BUFFER_SIZE 8
uint8_t buffer[BUFFER_SIZE];

void setup() {
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_PIN, moo);
  rf.TXInit(TX_PIN);
}

void loop() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
     buffer[i] = i * i;
     rf.transmitArray(BUFFER_SIZE, buffer);
  }
  digitalWrite(LED_PIN, digitalRead(LED_PIN)); //blink the LED on receive
  
  delay(100);
}
