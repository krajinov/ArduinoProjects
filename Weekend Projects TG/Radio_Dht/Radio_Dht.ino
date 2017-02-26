#include <dht.h>
#include "ManchesterRF.h" //https://github.com/cano64/ManchesterRF

#define TX_PIN 0 //any pin can transmit
#define LED_PIN 1
#define DHT11_PIN 3
#define arrSize 2

ManchesterRF rf(MAN_1200); //link speed, try also MAN_300, MAN_600, MAN_1200, MAN_2400, MAN_4800, MAN_9600, MAN_19200, MAN_38400
dht DHT;

uint8_t data[arrSize];

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  rf.TXInit(TX_PIN);
}

void loop() {
  // Read and set DHT values
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:       // if everything goes well
      sendDhtData();      // send data
      break;
    default:
      break;
  }
  delay(1500);
}

// Function for sending data
void sendDhtData() {
  data[0] = DHT.temperature;
  data[1] = DHT.humidity;
  rf.transmitArray(arrSize, data);
  digitalWrite(LED_PIN, digitalRead(LED_PIN)); //blink the LED on transmit
}


