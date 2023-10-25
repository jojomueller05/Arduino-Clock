#ifndef MICROSD_H
#define MICROSD_H

#include <Arduino.h>

//get the RTClib library
#include <SD.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <WiFiNINA.h>

void getJsonData(String dataArray[]);
void updateJson(String date, String time, bool isSet);
void getFileContent(const char *filename, WiFiClient &client);

String formatDate(String inputDate);
String formatTime(String inputTime);

#endif