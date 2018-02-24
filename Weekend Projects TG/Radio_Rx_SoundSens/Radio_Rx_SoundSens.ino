/*

  Manchester Receiver example

  In this example receiver will receive two 8 bit numbers per transmittion

*/


#include "ManchesterRF.h" //https://github.com/cano64/ManchesterRF



#define RX_PIN 4 //any pin can receive
#define LED_PIN 12

ManchesterRF rf(MAN_4800); //link speed, try also MAN_300, MAN_600, MAN_1200, MAN_2400, MAN_4800, MAN_9600, MAN_19200, MAN_38400

uint8_t a;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  rf.RXInit(RX_PIN);
}

void loop() {

  if (rf.available()) { //something is in RX buffer
    if (rf.receiveByte(a)) {
      //process the data
      //...
      Serial.println(a);
      if (a == 1) {
        digitalWrite(LED_PIN, HIGH); //blink the LED on receive
        delay(20);
      }

    }
  } else {
    digitalWrite(LED_PIN, LOW);
  }

}
