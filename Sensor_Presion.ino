//#include <DHT.h>
//#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
//#include <Adafruit_BMP085.h>
#include <Adafruit_BMP085_U.h>
    
       
    Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
     
    void setup(void) 
    {
      Serial.begin(9600);
      Serial.println("Pressure Sensor Test"); Serial.println("");
      
      /* Initialise the sensor */
      if(!bmp.begin())
      {
        /* There was a problem detecting the BMP085 ... check your connections */
        Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
        while(1);
      }
    }
     
    void loop(void) 
    {
      /* Get a new sensor event */ 
      sensors_event_t event;
      bmp.getEvent(&event);
     
      /* Display the results (barometric pressure is measure in hPa) */
      if (event.pressure)
      {
        /* Display atmospheric pressure in hPa */
        Serial.print("Pressure: "); Serial.print(event.pressure/10); Serial.println(" KPa");
        float temperature;
        bmp.getTemperature(&temperature);
        float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
        Serial.print("Altitude:    "); 
        Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                            event.pressure,
                                            temperature)); 
        Serial.println(" m");
      }
      else
      {
        Serial.println("Sensor error");
      }
      delay(250);
    }
