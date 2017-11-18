/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   You need to install this for ESP8266 development:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DHTPIN 14     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f3814f97c9e747ebb80129aa257e3825";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MT4209";
char pass[] = "23116f1c2558699";

float temp;
float hum;

BLYNK_READ(V1) {
  //Maybe...
  //  temp = 0;
//  int i = 100,
//  for(i=0; i<=100; i++){
//    temp += dht.readTemperature();
//    }
//  temp /= 100;
  temp = dht.readTemperature();
  Blynk.virtualWrite(V1, temp);
}
BLYNK_READ(V2) {
  hum = dht.readHumidity();
  Blynk.virtualWrite(V2, hum);
}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop()
{
  Blynk.run();
}
