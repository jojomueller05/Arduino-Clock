#include "RTC.h"

void getCurrentTime(char timeChar[6]) {
    DateTime now = rtc.now();

    int hour = now.hour();
    int minute = now.minute();
    sprintf(timeChar, "%02d:%02d", hour, minute);
}

void getCurrentDate(char dateChar[11]) {
    DateTime now = rtc.now();

    int day = now.day();
    int month = now.month();
    int year = now.year();
    
    sprintf(dateChar, "%02d.%02d.%04d", day, month, year);
}

