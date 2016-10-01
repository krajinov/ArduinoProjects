#define echoPin 2
#define trigPin 3
#define led 8

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int udaljenost, vrijeme;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  vrijeme = pulseIn(echoPin, HIGH);
  udaljenost = (vrijeme/2) / 29.1;
  if(udaljenost<=10){
  digitalWrite(led, HIGH);
  }
  else{
  digitalWrite(led, LOW);
  }
  Serial.print(udaljenost);
  Serial.print(" cm\n");
  delay(500);

}
