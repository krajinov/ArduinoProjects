/*******************************************************************************
 *  Project Title: ArduBot - Arduino robot
 *  Author: Ing. David Hrbaty
 *  Version: 1.1
 *  Revision Date: 21/12/2014
 *
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of either the GNU General Public License version 2
 *  or the GNU Lesser General Public License version 2.1, both as
 *  published by the Free Software Foundation.
 *
 * Schematic pinout:
 *
 * Left Servo motor:           D06
 * Right Servo motor:          D07
 * Head servo:                 D08
 * Ultrasonic sensor TRIG PIN: D09
 * Ultrasonic sensor ECHO PIN: D10
 * Speaker:                    D11
 * IR Receiver:                D12
 *******************************************************************************/

#include <IRremote.h>
#include <Servo.h>
// I have used TimeFreeTone, because original Tone library uses Timer, which I have used for timig servos and IR remote control.
// I haven`t used original Ping library for Ultrasonic sensor, because I have had problem with using Timer also.
#include <TimerFreeTone.h>
#include "pitches.h"

//Below are the symbolic constants. Instead of having to type in a non-sensical pin number each time we want to do something we can write an easy to understand name which represents the pin, the compiler will then replace the names with the numbers
#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED 13
#define SPEAKER 11
#define IR_RECEIVER 12

//Here we have created four 'objects', three for the servos and one for the IR receiver
Servo servo_head;

int LeftMotorForward = 3; // Pin 10 has Left Motor connected on Arduino boards.
int LeftMotorReverse = 4; // Pin 9 has Left Motor connected on Arduino boards.

int RightMotorForward = 5; // Pin 12 has Right Motor connected on Arduino boards.
int RightMotorReverse = 7; // Pin 13 has Right Motor connected on Arduino boards.

IRrecv irrecv(IR_RECEIVER);
decode_results results;    

//Below we are creating unsigned integer variables which we will use later on in the code. They are unsigned as they will only have postive values
unsigned int duration;
unsigned int distance;
unsigned int FrontDistance;
unsigned int LeftDistance;
unsigned int RightDistance;
unsigned int LeftDiagonalDistance;
unsigned int RightDiagonalDistance;

char choice;

char turnDirection;  // Gets 'l', 'r' or 'f' depending on which direction is obstacle free

// There are limits for obstacles:
const int distanceLimit = 20;           // Front distance limit in cm
const int sideDistanceLimit = 17;       // Side distance limit in cm
const int minTurnDistanceLimit = 11;       // Side distance limit in cm
const int turnTime = 300;               // Time needed to turn robot

int distanceCounter = 0;
int numcycles = 0;  // Number of cycles used to rotate with head during moving
int roam = 0;       // Switching between automatic and manual mode of moving
int mon = 0;        // Switching between monitor and manual mode of moving
int playSong = 0;   // Variable is set when any song is playing
int musicSong = 0;  // Variable is set to recognise which song is playing

int melodyTones[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
int melodyDurations[] = { 250, 125, 125, 250, 250, 250, 250, 250 };

int melodyTones2[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
int melodyDurations2[] = {200, 200, 200, 200, 200, 200, 500, 200, 200, 200, 200, 200, 200, 500};

void setup()                                            //This block happens once on startup
{
  Serial.begin(9600);                             
  //Here we are setting the pin modes. As we will sending out signals from the pins we set them as outputs
  pinMode(LED, OUTPUT);
  servo_head.attach(6); 
  servo_head.write(90);

  pinMode(LeftMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(LeftMotorReverse, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorReverse, OUTPUT);  // initialize the  pin as an output.

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  irrecv.enableIRIn();
  moveStop();
}

void loop()                                           //This block repeats itself while the Arduino is turned on
{

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    // if IR signal is received than decode it and decide what to do
    switch(results.value)
      {
      case 0xC26BF044: 
        Serial.println(" Moving Forward"); 
        moveForward(); 
        buzz();
        break;
      case 0xC4FFB646: 
        Serial.println(" Moving Backward");
        moveBackward();
        buzz();
        break;
      case 0x53801EE8: 
        Serial.println(" Moving Right");
        moveRight();  
        buzz();
        delay(turnTime);
        moveStop();
        break;
      case 0x758C9D82: 
        Serial.println(" Moving Left");
        moveLeft(); 
        buzz();
        delay(turnTime);
        moveStop();
        break; 
      case 0x8AF13528:
        Serial.println(" Moving stop");
        moveStop();
        buzz();
        break;
      case 0x3BCD58C8:
        Serial.println(" Playing music");
        moveStop();
        if(playSong == 0){
          if(musicSong == 0) {
            song1();
            musicSong = 1;
          }
          else {
            song2();
            musicSong = 0;
          }
        }        
        break;   
      case 0x974F362:
        Serial.println(" Automatic mode");
        mon = 0;
        moveStop();
        toggleRoam(); 
        buzz();
        break; 
      case 0x71C83AA6:
        Serial.println(" Monitoring mode");
        roam = 0;
        moveStop();
        toggleMonitor();
        buzz();
        break; 
      case 0xFFFFFFFF: 
        break;  
      default:
        Serial.println(" Unknown code received");
        break;
        
      }
      delay(100);
      irrecv.resume();
  }
  if(roam == 1){
    go();
  }
  
  
  if(mon == 1) {
    monitor();
  }

}
void toggleRoam(){                                    //This function toggle between autonomous and stop mode
  if(roam == 0){
    roam = 1;
    Serial.println("Activated Roam Mode");
  }
  else{
    roam = 0;
    moveStop();
    Serial.println("De-activated Roam Mode");
  }
}
void toggleMonitor(){                                  //This function toggle between monitor and stop mode
  if(mon == 0){
    mon = 1;
    moveStop();
    Serial.println("Activated Monitor Mode");
  }
  else{
    mon = 0;
    moveStop();
    Serial.println("De-activated Monitor Mode");
  }
}

void moveForward()                                    //This function tells the robot to go forward 
{
  Serial.println("");
  Serial.println("Moving forward");
  digitalWrite(RightMotorReverse, LOW);   
  digitalWrite(LeftMotorReverse, LOW);   
  digitalWrite(RightMotorForward, HIGH);   // turn the Right Motor ON
  digitalWrite(LeftMotorForward, HIGH);   // turn the Left Motor ON

}

void moveBackward()                                  //This function tells the robot to move backward
{
  Serial.println("");
  Serial.println("Moving backward");
  digitalWrite(RightMotorForward, LOW);   
  digitalWrite(LeftMotorForward, LOW);   
  digitalWrite(RightMotorReverse, HIGH);   // turn the Right Motor Reverse ON
  digitalWrite(LeftMotorReverse, HIGH);   // turn the Left Motor Reverse ON

}

void moveRight()                           //This function tells the robot to turn left
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(RightMotorForward, LOW);   // turn the Right Motor OFF
  digitalWrite(RightMotorReverse, HIGH);  // turn the Right Motor Reverse ON
  digitalWrite(LeftMotorReverse, LOW);    // turn the Left Motor OFF
  digitalWrite(LeftMotorForward, HIGH);   // turn the Left Motor Reverse ON
  
}

void moveLeft()                                    //This function tells the robot to turn right
{
  Serial.println("");
  Serial.println("Moving right");
 
  digitalWrite(RightMotorReverse, LOW);
  digitalWrite(LeftMotorForward, LOW);   // turn the Left Motor OFF
  digitalWrite(LeftMotorReverse, HIGH);
  digitalWrite(RightMotorForward, HIGH);
}

void moveStop()                                     //This function tells the robot to stop moving
{
  Serial.println("");
  Serial.println("Stopping");
  digitalWrite(RightMotorReverse, LOW);   
  digitalWrite(LeftMotorReverse, LOW);   
  digitalWrite(RightMotorForward,LOW);   // turn the Right Motor OFF
  digitalWrite(LeftMotorForward, LOW);   // turn the Left Motor OFF
}

int scan()                               //This function determines the distance things are away from the ultrasonic sensor
{
  long pulse;
  Serial.println("Scanning distance");
  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIG_PIN,LOW);
  pulse = pulseIn(ECHO_PIN,HIGH);
  distance = round( pulse*0.01657 );
  Serial.println(distance);
}

void watchsurrounding()
{ //Meassures distances to the right, left, front, left diagonal, right diagonal and asign them in cm to the variables rightscanval, 
  //leftscanval, centerscanval, ldiagonalscanval and rdiagonalscanval (there are 5 points for distance testing)
  scan();
  FrontDistance = distance;
  Serial.println("Front distance measuring done");
  if(FrontDistance < distanceLimit) 
  {
    moveStop;
  }
  servo_head.write(135);
  delay(100);
  scan();
  LeftDiagonalDistance = distance;
  Serial.println("Left diagonal distance measuring done");
  if(LeftDiagonalDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(165);
  delay(300);
  scan();
  LeftDistance = distance;
  Serial.println("Left distance measuring done");
  if(LeftDistance < sideDistanceLimit)
  {
    moveStop();
  }
  servo_head.write(135);
  delay(100);
  scan();
  LeftDiagonalDistance = distance;
  Serial.println("Left diagonal distance measuring done");
  if(LeftDiagonalDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(90);
  delay(100);
  scan();
  FrontDistance = distance;
  Serial.println("Front distance measuring done");
  if(FrontDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(55);
  delay(100);
  scan();
  RightDiagonalDistance = distance;
  Serial.println("Right diagonal distance measuring done");
  if(RightDiagonalDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(15);
  delay(100);
  scan();
  RightDistance = distance;
  Serial.println("Right distance measuring done");
  if(RightDistance < sideDistanceLimit)
  {
    moveStop();
  }
 
  servo_head.write(90); //Finish looking around (look forward again)
  delay(300);
  Serial.println("Measuring done");
}


char decide(){
   // Decide the right way without obstacles
  watchsurrounding();
  if (LeftDistance > RightDistance && LeftDistance > FrontDistance){
    if(RightDistance < minTurnDistanceLimit){
      Serial.println("Choice result is: BACK"); 
      choice = 'b';
    }else{
    Serial.println("Choise result is: LEFT");
    choice = 'l';
    }
  }
  else if (RightDistance > LeftDistance && RightDistance > FrontDistance){
    if(LeftDistance < minTurnDistanceLimit){
      Serial.println("Choice result is: BACK"); 
      choice = 'b';
      }else{
        Serial.println("Choise result is: RIGHT");
        choice = 'r';
        }
  }
  else if ( LeftDistance < sideDistanceLimit && RightDistance < sideDistanceLimit && FrontDistance < distanceLimit ) {
    Serial.println("Choice result is: BACK"); 
    choice = 'b';
  }
  else{
    Serial.println("Choise result is: FORWARD");
    choice = 'f';
  }
  return choice;
}

void go() {
  moveForward();
  ++numcycles;
  if(numcycles>40)  // After 40 cycles of code measure surrounding obstacles
  {
    Serial.println("Front obstancle detected");
    watchsurrounding();
    if( LeftDistance < sideDistanceLimit || LeftDiagonalDistance < sideDistanceLimit)
    {
      Serial.println("Moving: RIGHT");
      moveRight();
      delay(turnTime);
    }
    if( RightDistance < sideDistanceLimit || RightDiagonalDistance < sideDistanceLimit)
    {
      Serial.println("Moving: LEFT");
      moveLeft();
      delay(turnTime);
    }
    numcycles=0; //Restart count of cycles
  }
  scan();
  if( distance < distanceLimit)
  {
    distanceCounter++;
  }
  if( distance > distanceLimit)
  {
    distanceCounter = 0;
  }
  if(distanceCounter > 1)    // robot reachaed 3 times distance limit in front of the robot, so robot must stop immediately and decide right way
  {
    moveStop();
    turnDirection = decide();
     switch (turnDirection){
      case 'l':
        moveLeft();
        delay(turnTime);
        buzz();
        break;
      case 'r':
        moveRight();
        delay(turnTime);
        buzz();
        break;
      case 'b':
        moveBackward();
        delay(turnTime);
        moveRight();
        delay(turnTime);
        buzz();
        break;
      case 'f':
        buzz();
        break;
    }
    distanceCounter = 0;
  }
}


void monitor() {
    servo_head.write(90);
    delay(1000);    
    scan();    
    if(distance < distanceLimit)
    {
      servo_head.write(170);           //Move the servo to the left (my little servos didn't like going to 180 so I played around with the value until it worked nicely)
      delay(300);
      Serial.println(distance);
      servo_head.write(10);
      delay(300);
      servo_head.write(180);
      delay(300);
      servo_head.write(0);
      delay(300);
    }
    
    
}

void song1() {
  playSong = 1;
  for (int thisNote = 0; thisNote < 8; thisNote++) { // Loop through the notes in the array.
    TimerFreeTone(SPEAKER, melodyTones[thisNote], melodyDurations[thisNote]); // Play thisNote for duration.
    delay(50); // Short delay between notes. 
  }
  playSong = 0;
}
void song2() {
  playSong = 1;
  for (int thisNote = 0; thisNote < 14; thisNote++) { // Loop through the notes in the array.
    TimerFreeTone(SPEAKER, melodyTones2[thisNote], melodyDurations2[thisNote]); // Play thisNote for duration.
    delay(50); // Short delay between notes. 
  }
  playSong = 0;
}
void buzz(){
  TimerFreeTone(SPEAKER, NOTE_C7, 100);
  delay(50);
  TimerFreeTone(SPEAKER, NOTE_C6, 100);
}
void fart(){
 TimerFreeTone(SPEAKER, NOTE_C2, 200);
 delay(200);
 TimerFreeTone(SPEAKER, NOTE_C1, 400); 
 delay(400);
}
void disBuzz() {
  TimerFreeTone(SPEAKER, NOTE_C2, 100);
  delay(50);
  TimerFreeTone(SPEAKER, NOTE_C1, 100);
}
