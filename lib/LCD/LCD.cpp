#include "LCD.h"

//Update the LCD Screen
void updateLCD(String time, String date, bool set){
    lcd.setCursor(6,0);
    lcd.print(time);

    if (set){
        lcd.setCursor(0,1);
        lcd.print("SET");
        lcd.setCursor(6,1);
        lcd.print(date);
    } else {
        lcd.setCursor(6,1);
        lcd.print(date);
    }
}

//Show default value on LCD Screen
void defaultLCDValue(){
    lcd.setCursor(6,0);
    lcd.print("00:00");

    lcd.setCursor(6,1);
    lcd.print("00.00.0000");
}