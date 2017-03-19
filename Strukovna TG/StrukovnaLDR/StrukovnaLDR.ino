int analogPin = 3; //pin 2
int releyPin1 = 0; //pin 5
int releyPin2 = 2; //pin 6
int val = 0;

void setup()
{
  pinMode(releyPin1, OUTPUT);
  pinMode(releyPin2, OUTPUT);
  digitalWrite(releyPin1,HIGH);
  digitalWrite(releyPin2,HIGH);
  delay(2000);
}

void loop()
{
  val = analogRead(analogPin);    // read the input pin
  if(val < 200)
  {
    digitalWrite(releyPin1,LOW);
    digitalWrite(releyPin2,LOW);
    delay(200);
  }
  else
  {
    digitalWrite(releyPin1,HIGH);
    digitalWrite(releyPin2,HIGH);
  }
}
