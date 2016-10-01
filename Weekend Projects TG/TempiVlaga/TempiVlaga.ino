#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 6     // pin na kojemu je senzor Temp i Vlage
#define DHTTYPE DHT11   // DHT 11 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // pinovi na Arduinu na koje je spojen LCD(12(4), 11(6), 5(11), 4(12), 3(13), 2(14))

// Spojiti pin 1 (lijevo) of the sensor to +5V
// Spojiti pin 2 na DHTPIN
// Spojiti pin 4 (desno) u Uzemljenje
// Spojiti 10K otpornik sa senzorovog pin 2 (data) na pin 1 (power)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  
  lcd.begin(16, 2);
  lcd.print("Preracunavam...");
  lcd.setCursor(0, 1);
}

void loop() {
  // Očitavanje temperature i vlažnosti traje 250 milisekundi!
  // Očitanja senzora također mogu biti 2 sekunde u zakašnjenju(ovo je jako spor senzor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  delay(500);

  // provjeri da li su očitanja pravilna, ako je očitanje NaN (not a number- nije broj) došlo je do greške!
  if (isnan(t) || isnan(h)) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pogreska kod");
    lcd.setCursor(0,1);
    lcd.print("ucitavanja!!!");
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("'C"); 
 
    lcd.setCursor(0,1);
    lcd.print("Vlaga: ");
    lcd.print(h);
    lcd.print("%");
   
    delay(3000); 
  }
}
