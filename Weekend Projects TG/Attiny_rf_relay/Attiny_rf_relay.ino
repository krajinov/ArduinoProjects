/*
  Simple example for receiving

  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

#define RELAY 3

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {

    uint32_t value = mySwitch.getReceivedValue();
    if (value == 5522444) {
      digitalWrite(RELAY, LOW);
    }
    else if (value == 5522624) {
      digitalWrite(RELAY, HIGH);
    }
    mySwitch.resetAvailable();
  }
}
