int relay1 = 8;
int relay2 = 9;


void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  Serial.println("Test releja...");
  delay(2000);
}

void loop() {
  Serial.println("Paljenje 1. releja!");
  digitalWrite(relay1, LOW);
  delay(2000);
  Serial.println("Gasenje 1. releja!");
  digitalWrite(relay1, HIGH);
  delay(2000);
  Serial.println("Paljenje 2. releja!");
  digitalWrite(relay2, LOW);
  delay(2000);
  Serial.println("Gasenje 2. releja!");
  digitalWrite(relay2, HIGH);
  delay(2000);
}
