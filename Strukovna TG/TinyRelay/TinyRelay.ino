#define SWITCH1 0
#define SWITCH2 2
#define RELAY1 3
#define RELAY2 4

boolean btn1Pressed = false;
boolean btn2Pressed = false;

void setup() {
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
}

void loop() {
  int sw1 = digitalRead(SWITCH1);
  int sw2 = digitalRead(SWITCH2);
  if (sw1 == HIGH) {
    btn1Pressed = !btn1Pressed;
  }
  if (sw2 == HIGH) {
    btn2Pressed = !btn2Pressed;
  }
  if (btn1Pressed) {
    digitalWrite(RELAY1, LOW);
    delay(250);
  } else {
    digitalWrite(RELAY1, HIGH);
    delay(250);
  }
  if (btn2Pressed) {
    digitalWrite(RELAY2, LOW);
    delay(250);
  } else {
    digitalWrite(RELAY2, HIGH);
    delay(250);
  }
}
