/***
   This is a sketch for DHT11 sensor based on NRF2401l+
*/

#include "RF24.h"
#include <SPI.h>
#include <dht.h>

/*Request message from another node*/
int msg[1];
int reqWeather = 111;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 */
RF24 radio(9, 10);

/*Pipes for writing/reading respectively*/
uint8_t addresses[][6] = {"1Node", "2Node"};

/*Set channel above WiFi band.
  Usually frequencies above channel 100 are best.*/
int channel = 124;

/*Struct that defines DHT weather station information*/
struct weather {
  float temp;
  float hum;
};

typedef struct weather Weather;
/*Create a new variable of weather struct type*/
Weather data;

//DHT11 sensor on pin 5
dht DHT;
#define DHT11_PIN 5

void setup(void) {
  Serial.begin(9600);
  radio.begin();

  //Setting up a channel ,PA Level and DataRate
  radio.setChannel(channel);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  // Open a writing and reading pipe on this radio, with opposite addresses of
  // node that made request for this sensor informations
  radio.openReadingPipe(1, addresses[1]);
  radio.openWritingPipe(addresses[0]);
  // Start the radio listening for data
  radio.startListening();
}

void loop(void) {
  if (radio.available()) {
    radio.read(msg, 1);
    Serial.println("Message: ");
    Serial.println(msg[0]);

    //If message equals reqWeather get DHT data and send that data to another node
    if (msg[0] == reqWeather) {
      radio.stopListening();                      // First, stop listening so we can talk
      if (checkDHT()) {
        delay(30);
        radio.write(&data, sizeof(data));         // Send requested data back.
        Serial.println("Data sent");
      } else {
        Serial.println("DHT error");
      }
      radio.startListening();                     // Now, resume listening so we catch the next request.
    }
  }
}

boolean checkDHT() {
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK,\t");
      data.temp = DHT.temperature;                  // Get temperature reading from DHT
      data.hum = DHT.humidity;                      // Get humidity reading from DHT
      return true;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("Checksum error,\t");
      return false;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("Time out error,\t");
      return false;
    case DHTLIB_ERROR_CONNECT:
      Serial.print("Connect error,\t");
      return false;
    case DHTLIB_ERROR_ACK_L:
      Serial.print("Ack Low error,\t");
      return false;
    case DHTLIB_ERROR_ACK_H:
      Serial.print("Ack High error,\t");
      return false;
    default:
      Serial.print("Unknown error,\t");
      return false;
  }
}

