#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11 ,12);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() 
{
  // put your setup code here, to run once:
  // INDICAMOS QUE TENEMOS CONECTADA UNA PANTALLA DE 16X2
  Serial.begin(9600);
  bmp.begin();
  dht.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("   TRABAJO DE");
  lcd.setCursor(0,1);
  lcd.print("SIST. DE CONTROL");
  delay(5000);
}

void loop() 
{
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("data");
  //delay(500);
  sensors_event_t event;
  bmp.getEvent(&event);
  float temperature;
  bmp.getTemperature(&temperature);
  float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.clear();
  

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.clear();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  lcd.setCursor(0,0);  
  lcd.println(h,2);
  lcd.setCursor(5,0);
  lcd.print("% ");
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  lcd.setCursor(9,0);  
  lcd.println(t,2);
  lcd.setCursor(14,0);
  lcd.print(" C");
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  Serial.print("Pressure: "); Serial.print(event.pressure/10); Serial.println(" KPa");
  lcd.setCursor(0,1);  
  lcd.println(event.pressure/10,1);
  lcd.setCursor(5,1);
  lcd.print("Kpa");
  Serial.print("Altitude:    "); 
  Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                            event.pressure,
                                            temperature)); 
  Serial.println(" m");
  lcd.setCursor(9,1);  
  lcd.println(bmp.pressureToAltitude(seaLevelPressure,
                                            event.pressure,
                                            temperature),2);
  lcd.setCursor(14,1);
  lcd.print(" m");
  delay(2000);
  
}
