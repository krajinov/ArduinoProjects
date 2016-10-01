//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
void setup()
{
    Serial.begin(4800);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    Serial.println("Postavljeno sve!");
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      for(int i=0; i<buflen; i++){
        Serial.print(buf[i]);
        }
      Serial.println();
    }
   delay(300);
}
