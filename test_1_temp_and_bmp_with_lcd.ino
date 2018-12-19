
#include <LiquidCrystal.h>

#include <dht.h>
#include <BME280I2C.h>
#include <Wire.h>   

/* ==== Global Variables ==== */
BME280I2C bme;                   // Default : forced mode, standby time = 1000 ms
                              // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,
bool metric = false;

dht DHT;

#define DHT11_PIN 8

LiquidCrystal lcd(2,3,4,5,6,7);
void setup()
{
  Serial.begin(9600);
 lcd.begin(16,2); 
  lcd.setCursor(0,0);
 lcd.print("Weather Monitor ");
  while(!bme.begin()){
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
 delay(1500);
  lcd.clear();
}
 void loop(){
  float temp(NAN), hum(NAN), pres(NAN);
   uint8_t pressureUnit(3);                                           // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
   bme.read(pres, temp, hum, metric, pressureUnit);  

 Serial.print("\t\tPressure: ");
 Serial.print(pres);
 Serial.print(" atm");


  float altitude = bme.alt(metric);
 Serial.print("\t\tAltitude: ");
 Serial.print(altitude);
 Serial.print((metric ? "m" : "ft"));

  


  int chk = DHT.read11(DHT11_PIN);

  lcd.setCursor(0,0);
 lcd.print("T:");
 lcd.print(DHT.temperature, 0);
  lcd.print("C, H:");
 lcd.print(DHT.humidity, 0);
  lcd.print("%");
   lcd.setCursor(0,1);

     lcd.print("P:");
 lcd.print(pres, 0);
      lcd.print("atm,A:");
 lcd.print(altitude, 0);
lcd.print("ft");

 delay(2000);
 lcd.clear();
  

}
