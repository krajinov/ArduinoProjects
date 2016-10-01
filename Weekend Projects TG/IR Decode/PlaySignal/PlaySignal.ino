// This program allows an Arduino to power on/off a Duraflame heater using infrared
//
// Usage: hook up an IR led with Annode on pin 13.  Then send serial data "POWER"
// to the arduino.  It should flash the LED code.
//
// By Rick Osgood with code borrowed from adafruit.com
//

#define IRledPin 2
#define NumIRsignals 86
      
// This is the code I determined works for my Duraflame heater
int IRsignal[] = {
// ON, OFF (in 10's of microseconds)
  876, 448,
  52, 62,
  50, 64,
  48, 64,
  50, 64,
  48, 64,
  50, 64,
  52, 60,
  50, 64,
  50, 168,
  50, 170,
  50, 170,
  50, 168,
  54, 166,
  50, 170,
  50, 170,
  52, 166,
  52, 168,
  50, 64,
  48, 170,
  50, 64,
  48, 66,
  48, 64,
  50, 168,
  54, 60,
  50, 64,
  50, 168,
  52, 62,
  50, 170,
  48, 170,
  50, 170,
  52, 62,
  48, 170,
  50, 3894,
  874, 228,
  52, 2910,
  876, 226,
  52, 2910,
  874, 228,
  48, 2912,
  876, 226,
  50, 2912,
  876, 226,
  50, 2912,
  876, 226,
  50, 2912,
  878, 224,
  48, 2912,
  876, 226,
  52, 2908,
  876, 226,
  50, 2910,
  876, 222,
  54, 2910,
  874, 226,
  54, 2906,
  876, 226,
  50, 2910,
  876, 224,
  50, 2910,
  876, 224,
  52, 2908,
  876, 226,
  50, 2908,
  878, 224,
  54, 2906,
  874, 226,
  50, 2910,
  874, 226,
  50, 2910,
  874, 226,
  54, 2904,
  876, 226,
  50, 2908,
  876, 226,
  48, 2908,
  878, 224,
  50, 2908,
  874, 228,
  50, 2906,
  876, 226,
  50, 2908,
  874, 228,
  50, 2906,
  876, 226,
  50, 0};

void setup(void) {
  digitalWrite(IRledPin, LOW);   //Make sure LED starts "off"
  Serial.begin(9600);            //Initialize Serial port
}

void loop() {
  char data[6];
  int index = 0;

  delay(1000);  //Serial input seems to need some kind of short delay or the data gets screwed up.

  while (Serial.available() > 0) {            //Loop if there data on the serial line
    if (index < 5) {                          //Make sure we don't overflow
      data[index] = Serial.read();            //Load a character into the string
      index++;                                //Increment the index to get the next character
    }
  }
  
  data[5]='\0';  //Null terminate the string
  
  if (strcmp(data, "POWER") == 0){                //If the Arduino receives the POWER signal...
    Serial.println("SENDING SIGNAL!");
    for (int i = 0; i < NumIRsignals; i+=2) {         //Loop through all of the IR timings
      pulseIR(IRsignal[i]*10);              //Flash IR LED at 38khz for the right amount of time
      delayMicroseconds(IRsignal[i+1]*10);  //Then turn it off for the right amount of time
    }
  }                                         //Otherwise do nothing!
}

// This function allows us to PWM the IR LED at about 38khz for the sensor
// Borrowed from Adafruit!
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
