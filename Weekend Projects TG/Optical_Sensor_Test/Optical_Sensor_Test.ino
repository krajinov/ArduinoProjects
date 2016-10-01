/*
read analog data from A0 and send to PC via Serial port
*/

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog input 0:
  Serial.println(analogRead(A0));

  // wait a bit for the analog-to-digital converter
  // to stabilize after the last reading (min 2 milli sec):
  delay(200); //2000=2 sec
}
