//Brojač za 7 segmentni ekran(4 znamenke)
//Potrebne komponente:
//      1. Arduino Nano
//      2. 7 segmentni ekran
//      3. 74HC595 SHIFTReg
//      4. ULN2803A Darlington NPN Array
//      5. 1kOhm otpornik(7kom)

int latchPin = 2;
int dataPin = 3;
int clockPin = 4;

int CC1 = 6;
int CC2 = 7;
int CC3 = 8;
int CC4 = 9;
int CCP = 10;

int vrijeme = 100;

const byte sedam_segmentni[10] = 
                            { 63,  // = 0
                               6,  // = 1
                              91,  // = 2
                              79,  // = 3
                             102,  // = 4
                             109,  // = 5
                             125,  // = 6
                               7,  // = 7
                             127,  // = 8
                             111   // = 9
                             };

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(CC1, OUTPUT);
  pinMode(CC2, OUTPUT);
  pinMode(CC3, OUTPUT);
  pinMode(CC4, OUTPUT);
  pinMode(CCP, OUTPUT);
  digitalWrite(latchPin, LOW);
}
void loop(){

  for(byte broj1 = 0; broj1<10; broj1++){
    for(byte broj2 = 0; broj2<10; broj2++){
      for(byte broj3 = 0; broj3<10; broj3++){
        for(byte broj4 = 0; broj4<10; broj4++){
          for(byte t = 0; t<20; t++){
            postaviEkran(sedam_segmentni[broj1], CC1, vrijeme);
            postaviEkran(sedam_segmentni[broj2], CC2, vrijeme);
            postaviEkran(sedam_segmentni[broj3], CC3, vrijeme);
            postaviEkran(sedam_segmentni[broj4], CC4, vrijeme);
          }
        }
      }
    }
  }
}

