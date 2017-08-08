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

   This example shows how to use Arduino Ethernet shield (W5100)
   to connect your project to Blynk.
   Feel free to apply it to any other example. It's simple!

   NOTE: Pins 10, 11, 12 and 13 are reserved for Ethernet module.
         DON'T use them in your sketch directly!

 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEthernet.h>
#include "DHT.h"

#define DHTPIN 3     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0d31f50577384e12bfbe4fdedc647051";

float temp;
float hum;

BLYNK_READ(V1) {
  temp = dht.readTemperature();
  if (!isnan(temp)) {
    Blynk.virtualWrite(V1, temp);
  }
}
BLYNK_READ(V2) {
  hum = dht.readHumidity();
  if (!isnan(hum)) {
  Blynk.virtualWrite(V2, hum);
  }
}

void setup()
{
  Serial.begin(9600);
  //  Blynk.begin(auth);
  // You can also specify server.
  // For more options, see BoardsAndShields/Arduino_Ethernet_Manual example
  Blynk.begin(auth, "blynk-cloud.com", 8442);
  //  Blynk.begin(auth, IPAddress(192,168,168,62), 8888);
  dht.begin();
}

void loop()
{
  Blynk.run();
}
