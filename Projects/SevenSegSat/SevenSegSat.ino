//Prikaz vremena i temperature na 7 segmentnom ekranu(4 znamenke)
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

int comCat[5] = {6, 7, 8, 9, 10};       //  Katode za brojeve i katoda točaka L1, L2, L3

int vrijeme = 100;                  //  Vrijeme osvježavanja ekrana u mikrosekundama

unsigned long interval = 10000;     // Vrijeme prikaza sata(temperatura)
unsigned long previousMillis = 0;   // varijabla za bilježenje prvoga vremenskog stanja.

boolean satTemperatura;             // true = Prikaz sata, false = Temperatura
boolean subZeroTemp;
int digitBuffer[5] = {              //Buffer za spremanje znamenki
  0};

const byte sedam_segmentni[10] =   // Niz brojeva u binarnom obliku
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
const byte znakCelsius = 57;       //Binarna kombinacija za znak 'C'
const byte znakStupanj = 4;        //Binarna kombinacija za znak '°'
const byte znakDvotocka = 3;       //Binarna kombinacija za znak ':'

void setup() {
       Serial.begin(9600);
       setSyncProvider(RTC.get);   // dobavljanje vremena sa RTC
       if(timeStatus() != timeSet) 
         Serial.println("Unable to sync with the RTC");
       else
         Serial.println("RTC has set the system time");
  
       pinMode(latchPin, OUTPUT);
       pinMode(dataPin, OUTPUT);
       pinMode(clockPin, OUTPUT); 
       for(int i=0; i<5; i++){
        pinMode(comCat[i], OUTPUT);  
       }
       digitalWrite(latchPin, LOW);
       satTemperatura = true;               //Početak prikaza je prikaz vremena
       subZeroTemp = false;                 //Da li je temperatura ispod nule
}
void loop(){
        // Nakon što istekne određeni vremenski interval uradi sljedeće:
        if ((unsigned long)(millis() - previousMillis) >= interval) { 
          satTemperatura = !satTemperatura; //promjena prikaza sa vremena na temperaturu i obrnuto
          
          if(satTemperatura == false){      //očitavanje temperature
            int t = RTC.temperature();
            //Ako je temperatura ispod nule
            if(t<0){
              t=-t;
              subZeroTemp = true;
            }else{
              subZeroTemp = false;
            }
            
            float celsius = t / 4.0;
            int tempC = int(celsius*100);
            
            for(int i=0; i<5; i++){
              switch(i){ 
                case 0:
                digitBuffer[i] = sedam_segmentni[int(tempC)/1000];
                //Ako je 1. znamenka 0 i temperatura nije ispod nule
                if(digitBuffer[i]==sedam_segmentni[i] && !subZeroTemp){
                digitBuffer[i] = 0;
                }
                //A ako je temperatura ispod nule
                else if(subZeroTemp){
                  digitBuffer[i] = 64;
                }
                break;
                case 1:
                digitBuffer[i] = sedam_segmentni[(int(tempC)%1000)/100]+128;
                break;
                case 2:
                digitBuffer[i] = sedam_segmentni[(int(tempC)%100)/10];
                break;
                case 3:
                digitBuffer[i] = (int)znakCelsius;
                break;
                case 4:
                digitBuffer[i] = (int)znakStupanj;
                break;
                default: 
                // if nothing else matches, do the default
                // default is optional
                break;
                }
             }
          }
            
          previousMillis = millis();        //postavka brojača vremena na početno stanje
        }
        
        if(satTemperatura == false){        //prikazuj temperaturu
          for(int i=0; i<5; i++){
            postaviEkran(digitBuffer[i], comCat[i], vrijeme);
          }
        }
        else{                              //postavi i prikazuj vrijeme
          for(int i=0; i<5; i++){
            switch(i){
            case 0:
            digitBuffer[i] = sedam_segmentni[int (hour()/10)];
            break;
            case 1:
            digitBuffer[i] = sedam_segmentni[hour() - (int(hour()/10)*10)];
            break;
            case 2:
            digitBuffer[i] = sedam_segmentni[int(minute()/10)];
            break;
            case 3:
            digitBuffer[i] = sedam_segmentni[minute() - (int(minute()/10)*10)];
            break;
            case 4:
            digitBuffer[i] = znakDvotocka;
            break;
            default: 
            // if nothing else matches, do the default
            // default is optional
             break;
            }
          }
          for(int i=0; i<5; i++){
              postaviEkran(digitBuffer[i], comCat[i], vrijeme);
            }
         }
}

