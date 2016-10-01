#include <IRremote.h>

int RECV_PIN = 11;
int led = 3;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn(); // Start the receiver
  pinMode (led, OUTPUT);
}

void loop() {
  delay(180);
  if (irrecv.decode(&results) && results.value == 0xF4BA2988) {
    digitalWrite(led, HIGH);
    delay(200);
    irrecv.resume(); // Receive the next value
  }
  
  else if(irrecv.decode(&results) && results.value == 0x974F362)
  {  
    digitalWrite(led, LOW);  
    delay(200);
    irrecv.resume(); // Receive the next value
  }
  else{
    irrecv.resume(); 
  }
}
