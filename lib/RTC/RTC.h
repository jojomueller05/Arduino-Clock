#ifndef RTC_H
#define RTC_H

#include <Arduino.h>

//get the RTClib library
#include <RTClib.h> 

//get the rtc object:
extern RTC_DS3231 rtc; 

void getCurrentTime(char timeChar[6]);
void getCurrentDate(char dateChar[11]);
void setRTCDateTime(RTC_DS3231 rtc, String date, String time);
#endif