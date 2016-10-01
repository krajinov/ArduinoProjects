//Sat za 7 segmentni ekran(4 znamenke)
//Potrebne komponente:
//      1. Arduino Nano
//      2. 7 segmentni ekran
//      3. 74HC595 SHIFTReg
//      4. ULN2803A Darlington NPN Array
//      5. 1kOhm otpornik(7kom)
//      6. RTC modul - DS3231

#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)

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
       Serial.begin(9600);
       setSyncProvider(RTC.get);   // the function to get the time from the RTC
       if(timeStatus() != timeSet) 
         Serial.println("Unable to sync with the RTC");
       else
         Serial.println("RTC has set the system time");
  
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
        
        short desetkeSati = int (hour()/10);
        short jediniceSati= hour() - (int(hour()/10)*10);
        short desetkeMinuti = int (minute()/10);
        short jediniceMinuti = minute() - (int(minute()/10)*10);
      
        postaviEkran(sedam_segmentni[desetkeSati], CC1, vrijeme);
        postaviEkran(sedam_segmentni[jediniceSati], CC2, vrijeme);
        postaviEkran(sedam_segmentni[desetkeMinuti], CC3, vrijeme);
        postaviEkran(sedam_segmentni[jediniceMinuti], CC4, vrijeme);
        postaviEkran(3, CCP, vrijeme);
  
}

