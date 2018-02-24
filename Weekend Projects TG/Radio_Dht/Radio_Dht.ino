#include <dht.h>
#include "ManchesterRF.h" //https://github.com/cano64/ManchesterRF
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define TX_PIN 0 //any pin can transmit
#define LED_PIN 1
#define DHT22_PIN 3
#define arrSize 2
volatile boolean f_wdt = 1;

ManchesterRF rf(MAN_1200); //link speed, try also MAN_300, MAN_600, MAN_1200, MAN_2400, MAN_4800, MAN_9600, MAN_19200, MAN_38400
dht DHT;

int8_t data[arrSize];

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  rf.TXInit(TX_PIN);
  setup_watchdog(9); // approximately 4 seconds sleep
}

void loop() {
  // Wait for timed out watchdog
  // Flag is set when a watchdog timeout occurs
  if (f_wdt == 1) {
    // Reset flag
    f_wdt = 0;
    // Read and set DHT values
    int chk = DHT.read22(DHT22_PIN);
    switch (chk)
    {
      case DHTLIB_OK:       // if everything goes well
        sendDhtData();      // send data
        break;
      default:
        break;
    }
    // Set system into the sleep
    system_sleep();
  }
}

// Function for sending data
void sendDhtData() {
  data[0] = DHT.temperature;
  data[1] = DHT.humidity;
  rf.transmitArray(arrSize, data);
  digitalWrite(LED_PIN, digitalRead(LED_PIN)); //blink the LED on transmit
}

// Set system into the sleep state
// System wakes up when watchdog is timed out
void system_sleep() {
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out
  sbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter ON
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {

  byte bb;
  int ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt = 1; // set global flag
}


