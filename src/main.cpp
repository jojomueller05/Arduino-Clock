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

//wifi/webserver settings:
// visit http://192.168.4.1
char ssid[] = "Arduino Clock";        // Dein Netzwerk-SSID (Name)
char pass[] = "12345678";
int keyIndex = 0; 
int status = WL_IDLE_STATUS;
WiFiServer server(80);

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
  
  //button init:
  pinMode(ALARMBUTTON, INPUT_PULLUP);

  //wifi / webserver setup:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Kommunikation mit dem WiFi-Modul fehlgeschlagen!");
    // Nicht fortsetzen
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Bitte aktualisiere die Firmware");
  }

  Serial.print("Erstelle einen Access Point mit dem Namen: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);

  if (status != WL_AP_LISTENING) {
    Serial.println("Erstellen des Access Points fehlgeschlagen");
    // Nicht fortsetzen
    while (true);
  }

    // Warte 10 Sekunden auf eine Verbindung:
  delay(10000);

  // Starte den Webserver auf Port 80
  server.begin();


}

void loop() {
  // put your main code here, to run repeatedly:

  //LCD Screen:
  //get current date:
  char timeChar[6];
  getCurrentTime(timeChar);

  //get current time:
  char dateChar[11];
  getCurrentDate(dateChar);
  
  //getJsonData:
  String settings[3];
  getJsonData(settings);
  
  //settings date & time
  String dateString = settings[0];
  String timeString = settings[1];
  String clockSet = settings[2];

  
  if (clockSet == "true"){
    //updateLCD Screen:
    updateLCD(timeChar, dateChar, true);    
  } else {
      //updateLCD Screen:
      updateLCD(timeChar, dateChar, false);
  }

  // if settings == now run buzzer until button clicked.
  if (String(dateChar) == dateString && String(timeChar) == timeString && clockSet == "true"){

    while (digitalRead(ALARMBUTTON) == HIGH){
      //run buzzer
      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
      delay(1000);
      Serial.println();
      Serial.println("Buzzer is runing");
      Serial.println(); 
    }
        
      Serial.println();
      Serial.println("Button pressed!");
      Serial.println();   

      updateJson(dateString, timeString, false);

    // if date and time is set but "set" is false make it true again (for next day)
  } else if (dateString != "" && timeString != "" && clockSet == "false"){
    updateJson(dateString, timeString, true);
  }

  //webserver routing:
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Neuer Client verbunden");
    String request = client.readStringUntil('\r');

    if (request.indexOf("GET /") != -1) {
  // Wenn die Anforderung ein GET auf / ist, HTML zurückgeben
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  getFileContent("index.htm", client);

  // Schließe die Verbindung zum Client
  client.stop();
} else if (request.indexOf("POST /get-data") != -1) {
    // Wenn die Anforderung ein POST auf /get-data ist, JSON zurückgeben
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println();

    getFileContent("settings.txt", client);
} else if (request.indexOf("POST /") != -1) {
  // Wenn die Anforderung ein POST auf / ist
  // Hier analysieren wir den HTTP-Header, um die POST-Daten zu extrahieren
  int contentLength = 0;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line.startsWith("Content-Length: ")) {
      contentLength = line.substring(16).toInt();
    }
    if (line == "\r") {
      break; // Leerzeile am Ende des Headers
    }
  }

  // Hier lesen wir den HTTP-Body (Request-Daten)
  String body = client.readStringUntil('\r'); // Lies die Daten bis zum Ende des Requests

  // Analysiere die POST-Daten, um date und time zu extrahieren
  String dateValue = "";
  String timeValue = "";
  int dataIndex = body.indexOf("date=");
  int timeIndex = body.indexOf("time=");
  if (dataIndex != -1 && timeIndex != -1) {
    dateValue = body.substring(dataIndex + 5, timeIndex - 1);
    timeValue = body.substring(timeIndex + 5);
  }

  // Gib die extrahierten Daten aus
  Serial.println("Date: " + dateValue);
  Serial.println("Time: " + timeValue);

  String validDateString = formatDate(dateValue);
  String validTimeString = formatTime(timeValue);

  // Gib die extrahierten, neuen Daten aus
  Serial.println("Date: " + validDateString);
  Serial.println("Time: " + validTimeString);

  updateJson(validDateString, validTimeString, true);
  // Sende eine HTTP-Weiterleitung und beende die Verbindung
  client.println("HTTP/1.1 302 Found");
  client.println("Location: /");
  client.println();
  client.stop();
}
else {
      client.println("HTTP/1.1 404 Not Found");
      client.println("Content-Type: text/html");
      client.println();
      client.println("<html><body><h1>Nicht gefunden</h1></body></html>");
    }

    client.stop();
    Serial.println("Client getrennt");
  }
  


}

