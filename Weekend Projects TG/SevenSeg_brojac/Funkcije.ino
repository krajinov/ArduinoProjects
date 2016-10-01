void postaviEkran(byte broj, byte katoda, byte trajanje){
  shiftOut(dataPin, clockPin, MSBFIRST, broj);
  digitalWrite(latchPin, HIGH);
  digitalWrite(katoda, HIGH);
  delayMicroseconds(trajanje);
  digitalWrite(latchPin, LOW);
  digitalWrite(katoda, LOW);
  delayMicroseconds(trajanje/10);
  }
