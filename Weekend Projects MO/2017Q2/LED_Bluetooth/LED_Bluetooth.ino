#include <SoftwareSerial.h>

#define led 5

char serialChar;
String command = "";
boolean ledon = false;
SoftwareSerial btSerial(10, 11); // RX, TX

void setup()
{
  //Init serials
  Serial.begin(57600);
  btSerial.begin(9600);
  //Led pin to output
  pinMode(led, OUTPUT);
}

void loop()
{
  //Read Bluetooth serial
  while (btSerial.available() > 0)
  {
    serialChar = ((byte)btSerial.read());
    if (serialChar == ':')
      break;
    else
      command += serialChar; //Append current char to command string
    delay(1);
  }
  //If command string isn't empty...
  if (command.length() > 0) {

    if (command == "TO")        // Turn on LED command from phone
    {
      ledOn();
      ledon = true;
      Serial.println(command);
    }
    else if (command == "TF")   // Turn off LED command from phone
    {
      ledOff();
      ledon = false;
      Serial.println(command);
    }
    else if ((command.toInt() >= 0) && (command.toInt() <= 255))
    {
      if (ledon == true)
      {
        // Change brightness of LED
        analogWrite(led, command.toInt());
        Serial.println(command);
        delay(10);
      }
    }
    command = "";
  }

}

void ledOn() {
  analogWrite(led, 255);
  delay(1);
}

void ledOff() {
  analogWrite(led, 0);
  delay(1);
}



