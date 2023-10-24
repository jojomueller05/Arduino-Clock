#include <Arduino.h>

//Public Librarys:
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "rgb_lcd.h"
#include <RTClib.h> 
#include <SD.h> 
#include <ArduinoJson.h> 


//Own Modules:
#include "LCD.h"


//LCD setup:
rgb_lcd lcd;

const int colorR = 192;
const int colorG = 81;
const int colorB = 209;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

    //lcd setup
    lcd.begin(16, 2); // Initialize LCD here
    lcd.setRGB(colorR, colorG, colorB);
    defaultLCDValue();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World");

}

