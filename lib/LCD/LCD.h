#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

//get the rgb_lcd library
#include "rgb_lcd.h"

//get the lcd setup
extern rgb_lcd lcd;
extern const int colorR;
extern const int colorG;
extern const int colorB;

//Update LCD Screen
void updateLCD(String time, String date, bool set);

//Show default value on LCD Screen
void defaultLCDValue();


#endif