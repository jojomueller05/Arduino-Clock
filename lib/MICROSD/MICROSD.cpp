#include "MICROSD.h"

void getJsonData(String dataArray[]) {
    // Öffnen der JSON-Datei
    StaticJsonDocument<256> doc;
    File file = SD.open("settings.txt");

    if (file) {
        DeserializationError error = deserializeJson(doc, file);

        if (!error) {
            // Speichern der JSON-Daten im Array
            dataArray[0] = doc["date"].as<String>();
            dataArray[1] = doc["time"].as<String>();
            
            // Überprüfen und speichern des boolschen Werts "set"
            bool isSet = doc["set"];
            dataArray[2] = isSet ? "true" : "false"; // Konvertiere bool in String "true" oder "false"
        } else {
            Serial.println("Fehler beim Lesen der JSON-Datei!");
        }
        file.close();
    } else {
        Serial.println("Fehler beim Öffnen der Datei!");
    }
}


void updateJson(String date, String time, bool isSet) {
    StaticJsonDocument<256> doc;
    doc["date"] = date;
    doc["time"] = time;
    doc["set"] = isSet;

    File file = SD.open("settings.txt", O_WRITE);

    if (file) {
        if (serializeJson(doc, file) == 0) {
            Serial.println("Fehler beim Schreiben der JSON-Datei!");
        } else {
            Serial.println("In JSON-Datei geschrieben!");
        }
        file.close();
    } else {
        Serial.println("Konnte settings.txt nicht öffnen!");
    }
}


String getFileContent(String filename) {
  String fileContent = "";

  File file = SD.open(filename);

  if (file) {
    while (file.available()) {
      char c = file.read();
      fileContent += c;
    }

    file.close();
  } else {
    // Fehler beim Öffnen der Datei
    fileContent = "Error: Couldn't read file!";
  }

  return fileContent;
}
