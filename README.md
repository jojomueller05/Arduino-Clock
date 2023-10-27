# SMART CLOCK

A Smart Clock with a Web GUI, built with an Arduino for a School project.

**Usage:**<br>
1. Start the Arduino
2. Connect to the WiFi Arduino Clock
3. Open up your Browser and go to [http://192.168.4.1](http://192.168.4.1)
4. Change the Time / Set a Alarm

# Hardware Components

- Arduino MKR WiFi 1010
- Robotdyn MicroSD board
- Grove-LCD RGB Backlight V2.0
- Button 
- Buzzer V1.2
- Precision I2C RTC
- SD Card 
- Micro USB to USB Type A Cable

# Installation Guid

- Make sure you've got all the parts needed for assembling the Arduino.
(Details about the assembling prozess are coming soon).
- Download the [Arduino-Clock-Frontend](https://github.com/jojomueller05/Arduino-Clock-frontend) Repository
- Copy all files from the Repo to the SD Card and insert it into the SD Card module
- Download Microsoft Visual Studio Code and Plattform.io
- Clone the Repository & Open it with Plattform.io 
- Connect the Arduino to your PC with a Micro USB to USB Type A Cable
- Compile and upload the code
# Bugs
1. Website isn't Responsive

2. contentLength is asigned but never used on line 236 and 294