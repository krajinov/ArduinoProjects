#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>

byte mac[] = { 0x08, 0x4D, 0x05, 0xAB, 0xA1, 0xB1 };

// IP address if DHCP fails
IPAddress ip(192,168,168,170);

// Create aREST instance
aREST rest = aREST();

// Initialize the Ethernet server library
EthernetServer server(80);

void setup() {
  
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  // Give name and ID to device
  rest.set_id("008");
  rest.set_name("bole");

  // Start the Ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  
  // Start server
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  
  // listen for incoming clients
  EthernetClient client = server.available();
  rest.handle(client);
  
}
