
// include the library code:
#include <LiquidCrystal.h>
#include "Adafruit_CCS811.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//define BME pins
#define BME_SCK 13
#define BME_MISO 7
#define BME_MOSI 6
#define BME_CS 10

//initialize sealevel pressure
#define SEALEVELPRESSURE_HPA (1012.7)

Adafruit_CCS811 ccs;
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI


// initialize the library
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  // set up LCD
  lcd.begin(16, 2);
  
  // serial communication
  Serial.begin(9600);

   bool status;
   
    status = bme.begin();  
    if (!status) {
        Serial.println("check wiring");
        while (1);
    }
    
  if(!ccs.begin()){
    Serial.println("Failed");
    while(1);
  }

  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

void loop() {

//read and write CCS811 data
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      Serial.println();
      lcd.clear();
      Serial.print("CO2: ");
      lcd.print("CO2: "); 
      Serial.print(ccs.geteCO2());
      lcd.print(ccs.geteCO2());
      Serial.print(" ppm,   ");
      lcd.print(" ppm ");

      lcd.setCursor(0,1);
      Serial.print(" TVOC: ");
      lcd.print("TVOC: ");
      Serial.print(ccs.getTVOC());
      lcd.print(ccs.getTVOC());
      Serial.print(" ppm,   ");
      lcd.print(" ppm ");
      
      delay(5000);
   
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }

//read and write BME280 data
    bmeValues1();
    delay(5000);
    bmeValues2();
    delay(5000);
}

void bmeValues1() {
    
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.print("Temp: ");
    lcd.print("Temp: ");
    Serial.print(bme.readTemperature()*9/5 +32);
    lcd.print(bme.readTemperature()*9/5 +32);
    Serial.print(" *F, ");
    lcd.print(" *F");
    Serial.print("Humidity: ");
    lcd.setCursor(0,1);
    lcd.print("Humid: ");
    Serial.print(bme.readHumidity());
    lcd.print(bme.readHumidity());
    Serial.print(" %");
    lcd.print(" %");
    
