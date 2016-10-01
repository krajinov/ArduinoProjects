int latchPin = 2;
int dataPin = 3;
int clockPin = 4;
int katodaPrvog = 6;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(katodaPrvog, OUTPUT);
}
void loop(){
digitalWrite(katodaPrvog, HIGH);
//0
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 63);
digitalWrite(latchPin, HIGH);
delay(1000);
//1
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 6);
digitalWrite(latchPin, HIGH);
delay(1000);
//2
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 91);
digitalWrite(latchPin, HIGH);
delay(1000);
//3
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 79);
digitalWrite(latchPin, HIGH);
delay(1000);
//4
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 102);
digitalWrite(latchPin, HIGH);
delay(1000);
//5
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 109);
digitalWrite(latchPin, HIGH);
delay(1000);
//6
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 125);
digitalWrite(latchPin, HIGH);
delay(1000);
//7
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 7);
digitalWrite(latchPin, HIGH);
delay(1000);
//8
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 127);
digitalWrite(latchPin, HIGH);
delay(1000);
//9
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 103);
digitalWrite(latchPin, HIGH);
delay(1000);
digitalWrite(katodaPrvog, LOW);
delay(500);
}
