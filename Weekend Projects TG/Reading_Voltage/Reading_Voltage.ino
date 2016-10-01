int potPin = A0;
int readValue;
float Voltage;

void setup() {
  pinMode(potPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  readValue = analogRead(potPin);
  Voltage = (4.96/1023.0)*readValue;
  Serial.println(Voltage);
  delay(250);

}
