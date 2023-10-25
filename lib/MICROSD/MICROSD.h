#ifndef MICROSD_H
#define MICROSD_H

#include <Arduino.h>

//get the RTClib library
#include <SD.h>
#include <ArduinoJson.h>
#include <Wire.h>

void getJsonData(String dataArray[]);
void updateJson(String date, String time, bool isSet);
String getFileContent(String filename);

#endif