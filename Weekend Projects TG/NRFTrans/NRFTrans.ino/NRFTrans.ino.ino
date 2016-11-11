#include  <SPI.h>
#include "RF24.h"
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = 3;

void setup(void){
 Serial.begin(9600);
 radio.begin();
 radio.setChannel(120);
 radio.setPALevel(RF24_PA_MAX);
 radio.setDataRate(RF24_250KBPS);
 radio.openWritingPipe(pipe);
 pinMode(SW1, INPUT);
 }

void loop(void){
 if (digitalRead(SW1) == HIGH){
 msg[0] = 111;
 if (!radio.write(msg, 1)){
   Serial.println("failed");
 }
 Serial.println("Button pressed!");
 }
 else{
  msg[0] = 000;
  radio.write(msg, 1);
  }
 
 }
