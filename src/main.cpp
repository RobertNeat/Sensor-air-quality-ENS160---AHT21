/***************************************************************************
  ENS160 + AHT21 sensor (standard reading mode)
  Connections from sensors to esp_32:
  VIN - to 3V3 esp_32 pin 
  3V3 - DON't CONNECT (weak power)
  GND - to GND esp_32 pin
  SCL - to GPIO_22 esp_32 pin
  SDA - to GPIO_21 esp_32 pin
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_AHTX0.h>    // AHT21 library
#include "ScioSense_ENS160.h"  // ENS160 library

Adafruit_AHTX0 aht;

int tempC;  //celsjus degrees
int humidity; //relative humidity (0 to 100%)

ScioSense_ENS160      ens160(ENS160_I2CADDR_1);

int aqi = 0;  //air quality index (1 to 5)
int tvoc = 0; //total volatile Organic Compounds  ppb concentration (0 - 65 000 ppb)
int eco2 = 0; //CO2 equivalent (400 to 65 000 ppm)

void setup() {
  Serial.begin(9600);
  Serial.println("#-----/ENS160 (Indoor Air Quiality) + AHT21 (temperature,humidity)/-----#");

  ens160.begin();
  Serial.println(ens160.available() ? "done." : "failed!");
  if (ens160.available()) {
    // Print ENS160 versions
    Serial.print("\tRev: "); Serial.print(ens160.getMajorRev());
    Serial.print("."); Serial.print(ens160.getMinorRev());
    Serial.print("."); Serial.println(ens160.getBuild());
  
    Serial.print("\tStandard mode ");
    Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
  }else{
    Serial.print("Connect following (not connected):");
    Serial.print("GND - to ESP32 GND");
    Serial.print("VIN - to ESP32 3V3");
    Serial.print("SCL - to ESP32 GPIO 22");
    Serial.print("SDA - to ESP32 GPIO 21");
  }


  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  
}


void loop() {
  
  ///// AHT20 start
  sensors_event_t humidity1, temp;
  aht.getEvent(&humidity1, &temp);// populate temp and humidity objects with fresh data
  tempC = (temp.temperature);
  humidity = (humidity1.relative_humidity);

  Serial.print("Temperature: "); 
  Serial.print(tempC); 
  Serial.println(" degrees C");

  Serial.print("Humidity: "); 
  Serial.print(humidity); 
  Serial.println("% rH");

  if (ens160.available()) {
    aqi = ens160.getAQI();
    tvoc = ens160.getTVOC();
    eco2 = ens160.geteCO2();

    // Give values to Air Quality Sensor.
    ens160.set_envdata(tempC, humidity);

    ens160.measure(true);
    ens160.measureRaw(true);
  
    Serial.print("AQI: ");
    Serial.println(aqi);

    Serial.print("TVOC: ");
    Serial.print(tvoc);
    Serial.println("ppb");


    Serial.print("eCO2: ");
    Serial.print(eco2);
    Serial.println("ppm");
    
    //Serial.print("R HP0: ");Serial.print(ens160.getHP0());Serial.print("Ohm\t");
    //Serial.print("R HP1: ");Serial.print(ens160.getHP1());Serial.print("Ohm\t");
    //Serial.print("R HP2: ");Serial.print(ens160.getHP2());Serial.print("Ohm\t");
    //Serial.print("R HP3: ");Serial.print(ens160.getHP3());Serial.println("Ohm");
  }
  delay(1000);

}


/*
Temperature: 28 degrees C
Humidity: 55% rH
AQI: 1
TVOC: 27ppb
eCO2: 409ppm

*/