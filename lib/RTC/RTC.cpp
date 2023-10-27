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

void setRTCDateTime(RTC_DS3231 rtc, String date, String time) {
  // Zerlege den Eingabe-String "date" in Tag, Monat und Jahr
  int day, month, year;
  sscanf(date.c_str(), "%d.%d.%d", &day, &month, &year);

  // Zerlege den Eingabe-String "time" in Stunden und Minuten
  int hours, minutes;
  sscanf(time.c_str(), "%d:%d", &hours, &minutes);

  // Erstelle ein DateTime-Objekt mit der eingegebenen Zeit
  DateTime newDateTime(year, month, day, hours, minutes, 0);

  // Setze die Uhrzeit auf das RTC-Modul
  rtc.adjust(newDateTime);
}