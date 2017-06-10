// My results:
// Raw Ranges: X: 402-608, Y: 400-605, Z: 413-617
// 505, 503, 617 :: 0.00G, 0.00G, 1.00G


const uint8_t xInput = A0;
const uint8_t yInput = A1;
const uint8_t zInput = A2;
 
// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis

uint16_t xRawMin = 402;
uint16_t xRawMax = 608;
 
uint16_t yRawMin = 400;
uint16_t yRawMax = 605;
 
uint16_t zRawMin = 413;
uint16_t zRawMax = 617;
 
// Take multiple samples to reduce noise
const int sampleSize = 15;
 
void setup() 
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}
 
void loop() 
{
  uint16_t xRaw = ReadAxis(xInput);
  uint16_t yRaw = ReadAxis(yInput);
  uint16_t zRaw = ReadAxis(zInput);
  
  Serial.print("Raw Ranges: X: ");
  Serial.print(xRawMin);
  Serial.print("-");
  Serial.print(xRawMax);
  
  Serial.print(", Y: ");
  Serial.print(yRawMin);
  Serial.print("-");
  Serial.print(yRawMax);
  
  Serial.print(", Z: ");
  Serial.print(zRawMin);
  Serial.print("-");
  Serial.print(zRawMax);
  Serial.println();
  Serial.print(xRaw);
  Serial.print(", ");
  Serial.print(yRaw);
  Serial.print(", ");
  Serial.print(zRaw);
  
  // Convert raw values to 'milli-Gs"
  long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
  long yScaled = map(yRaw, yRawMin, yRawMax, -1000, 1000);
  long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  Serial.print(" :: ");
  Serial.print(xAccel);
  Serial.print("G, ");
  Serial.print(yAccel);
  Serial.print("G, ");
  Serial.print(zAccel);
  Serial.println("G");
  
  delay(500);
}
 
//
// Read "sampleSize" samples and report the average
//
uint16_t ReadAxis(uint8_t axisPin)
{
  long reading = 0;
  
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
    delay(1);
  }
  return reading/sampleSize;
}

