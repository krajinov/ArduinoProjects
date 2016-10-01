boolean onoff = false;
int stanjeSklopke = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  stanjeSklopke = digitalRead(2);
  
  if(stanjeSklopke == LOW){
  }
  else if(stanjeSklopke == HIGH && onoff == false){
  onoff = true;
  delay(250);
  }
  else if(stanjeSklopke == HIGH && onoff == true){
  onoff = false;
  delay(250);
  }
  
  if(onoff == false){
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  }else{
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  
  delay(100);
  
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  
  delay(100);
  }
}
