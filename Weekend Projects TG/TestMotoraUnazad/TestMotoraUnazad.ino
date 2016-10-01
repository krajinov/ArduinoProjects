int LeftMotorForward = 3; // Pin 10 has Left Motor connected on Arduino boards.
int LeftMotorReverse = 4; // Pin 9 has Left Motor connected on Arduino boards.

int RightMotorForward = 5; // Pin 12 has Right Motor connected on Arduino boards.
int RightMotorReverse = 2 ; // Pin 13 has Right Motor connected on Arduino boards.


void setup()
{
  pinMode(LeftMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(LeftMotorReverse, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorReverse, OUTPUT);  // initialize the  pin as an output.
}

// The following Loop is to make the Robot Reverse
void loop()

{
   digitalWrite(RightMotorReverse, HIGH);   // turn the Right Motor ON
   digitalWrite(LeftMotorReverse, HIGH);   // turn the Left Motor ON
   delay(10000);               // wait for  10 seconds
 
   digitalWrite(RightMotorForward,LOW);   // turn the Right Motor OFF
   digitalWrite(LeftMotorForward, LOW);   // turn the Left Motor OFF
   delay(10000);               // wait for  10 seconds
}
