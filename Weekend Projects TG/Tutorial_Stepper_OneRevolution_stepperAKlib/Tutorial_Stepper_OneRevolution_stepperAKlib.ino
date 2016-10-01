
/* 
 Stepper Motor Control - one revolution
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.  
 
  
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 Adapted for Arduino Kit geared stepper motor (28BYJ-48) by Rudy Schlaf 2/2014
 
 */

#include <StepperAK.h> //use modified stepper library with 1000/0100/0010/0001 magnet firing sequence. Put library in your library folder.

#define gearratio 64 //1:64 gear ratio
const int stepsPerRevolution = 2048;  //the Arduino Kit motor is geared down. By experiment I determined that 2048 steps turn the shaft one round.
                                     

// instantiate a 4-wire stepper on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

void setup() {
  // set the speed at 0.15 rpm (0.15-0.2 (dep. on particular motor) seems the fastest they can go...set it higher and it stops moving, just makes noises):
  myStepper.setSpeed(0.15*gearratio);//the motor appears to be geared down 1/64, meaning that the speed needs to be set 64x.
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
   Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
  
   // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500); 
}

