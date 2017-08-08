class LM335
{
    const float tempCoef = 0.010076;
    float cal;
    int pin;
  public:
    LM335(float mCal, int mPin);
    float measureV();
    float measureK();
    float measureC();
    float measureF();
    float measureRankine();
};

LM335::LM335(float mCal, int mPin)
{
  cal = mCal;
  pin = mPin;
}
float LM335::measureV()
{
  float uzorakTem = 0;
  float retVal;
  for (int i = 0; i < 50; i++) {
    uzorakTem += (float) analogRead(pin);
    delayMicroseconds(1);
  }
  retVal = uzorakTem / 50;
  retVal = (retVal * cal) / 1024.0;
  return retVal;
}
float LM335::measureK()
{
  return measureV() / tempCoef; //10mV/k
}
float LM335::measureC()
{
  return (measureV() / tempCoef) - 273.15;
}
float LM335::measureF()
{
  return (((measureV() / tempCoef) - 273.15) * 1.8) + 32;
}
float LM335::measureRankine()
{
  return measureF() + 458.67;
}

LM335 mTemp(5.0, A0);//supply volts, analog pin

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  Serial.print(mTemp.measureV());
  Serial.println(" volts");
  Serial.println("Temperatures: ");
  Serial.print("Kelvin: ");
  Serial.println(mTemp.measureK());
  Serial.print("Fahrenheit: ");
  Serial.println(mTemp.measureF());
  Serial.print("Celsius: ");
  Serial.println(mTemp.measureC());
  Serial.print("Rankine: ");
  Serial.println(mTemp.measureRankine());
  delay(1000);
}
