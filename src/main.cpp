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
#include "RTC.h"
#include "MICROSD.h"

//LCD settings:
rgb_lcd lcd;
const int colorR = 192;
const int colorG = 81;
const int colorB = 209;

//rtc settings:
RTC_DS3231 rtc;

//SD Card settigns:
const int SDCARD = 4;

//BUZZER Settings:
const int BUZZER = 5;

//ALARMBUTTON Settings:
const int ALARMBUTTON = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //lcd init:
  lcd.begin(16, 2); // Initialize LCD here
  lcd.setRGB(colorR, colorG, colorB);
  defaultLCDValue();

  //rts init:
  Wire.begin();
    //check if rtc is ready
    if (!rtc.begin()) {
      Serial.println("RTC konnte nicht initialisiert werden!");
      while (1);
    }

  // SD card init:
  if (!SD.begin(SDCARD)) {
    Serial.println("SD-Karte konnte nicht initialisiert werden.");
    while (1);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hello World");

  //LCD Screen:
  //get current date:
  char timeChar[6];
  getCurrentTime(timeChar);

  //get current time:
  char dateChar[11];
  getCurrentDate(dateChar);
  
  //updateLCD Screen:
  updateLCD(timeChar, dateChar, true);

  //getJsonData:
  String settings[2];
  getJsonData(settings);
  
  //settings date & time
  String dateString = settings[0];
  String timeString = settings[1];
  
  // if settings == now run buzzer until button clicked.
  if (dateChar == dateString && timeChar == timeString){
    if (digitalRead(ALARMBUTTON) == LOW){
      //run buzzer
      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
      delay(1000);
    }

  }

  
}

