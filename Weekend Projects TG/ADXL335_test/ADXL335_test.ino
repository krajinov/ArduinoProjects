// Raw Ranges: X: 394-598, Y: 392-594, Z: 406-608
// 492, 487, 607 :: -0.04G, -0.06G, 1.00G

const int xInput = A0;
const int yInput = A1;
const int zInput = A2;
const int buttonPin = 2;
 
// Raw Ranges:
// initialize to mid-range and allow calibration to
// find the minimum and maximum for each axis

int xRawMin = 394;
int xRawMax = 598;
 
int yRawMin = 392;
int yRawMax = 594;
 
int zRawMin = 406;
int zRawMax = 608;
 
// Take multiple samples to reduce noise
const int sampleSize = 10;
 
void setup() 
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}
 
void loop() 
{
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);
  
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
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
