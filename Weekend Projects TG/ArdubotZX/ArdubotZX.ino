// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h> 

// DC motor on M1&M2
AF_DCMotor motorL(1);
AF_DCMotor motorR(2);
// DC hobby servo
Servo servo_head;

#define TRIG_PIN 15
#define ECHO_PIN 14
#define LED 13

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
const int turnTime = 2000;               // Time needed to turn robot

int distanceCounter = 0;
int numcycles = 0;  // Number of cycles used to rotate with head during moving

int i;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Initializing Ardubot!");
  
  // turn on servo
  servo_head.attach(10);
  servo_head.write(90);
    
  // turn on motor #2
  motorL.setSpeed(255);
  motorR.setSpeed(255);
  moveStop();
  delay(1500);
}

// Test the DC motor, stepper and servo ALL AT ONCE!
void loop() {
 go();
}


//------------------------------//
//Scan surrounding methods//
//------------------------------//

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
  delay(50);
  scan();
  LeftDiagonalDistance = distance;
  Serial.println("Left diagonal distance measuring done");
  if(LeftDiagonalDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(165);
  delay(50);
  scan();
  LeftDistance = distance;
  Serial.println("Left distance measuring done");
  if(LeftDistance < sideDistanceLimit)
  {
    moveStop();
  }
  
  servo_head.write(90);
  delay(150);
  scan();
  FrontDistance = distance;
  Serial.println("Front distance measuring done");
  if(FrontDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(55);
  delay(50);
  scan();
  RightDiagonalDistance = distance;
  Serial.println("Right diagonal distance measuring done");
  if(RightDiagonalDistance < distanceLimit)
  {
    moveStop();
  }
  servo_head.write(15);
  delay(50);
  scan();
  RightDistance = distance;
  Serial.println("Right distance measuring done");
  if(RightDistance < sideDistanceLimit)
  {
    moveStop();
  }
 
  servo_head.write(90); //Finish looking around (look forward again)
  delay(150);
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

//-----------------------//
//Control motors methods //
//-----------------------//

//Stani
void moveStop(){
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

//Naprijed
void moveForward(){
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}

//Nazad
void moveBackward(){
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
}

//Desno
void moveRight(){
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
}

//Lijevo
void moveLeft(){
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
}

//Automatsko upravljanje
void go() {
  moveForward();
  ++numcycles;
  if(numcycles>5)  // After 40 cycles of code measure surrounding obstacles
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
  if(distanceCounter > 2)    // robot reachaed 3 times distance limit in front of the robot, so robot must stop immediately and decide right way
  {
    moveStop();
    turnDirection = decide();
     switch (turnDirection){
      case 'l':
        moveLeft();
        delay(turnTime);
//        buzz();
        break;
      case 'r':
        moveRight();
        delay(turnTime);
//        buzz();
        break;
      case 'b':
        moveBackward();
        delay(turnTime);
        moveRight();
        delay(turnTime);
//        buzz();
        break;
      case 'f':
//        buzz();
        break;
    }
    distanceCounter = 0;
  }
}


  
