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
    // Schritt 1: Datei öffnen
    File file = SD.open("settings.txt", FILE_WRITE | O_TRUNC);

    if (file) {

        file.close();
    } else {
        Serial.println("Konnte settings.txt nicht öffnen!");
        return;
    }

    // Schritt 5: Die Datei erneut öffnen und Daten schreiben
    file = SD.open("settings.txt", FILE_WRITE);

    if (file) {
        StaticJsonDocument<256> doc;
        doc["date"] = date;
        doc["time"] = time;
        doc["set"] = isSet;

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



void getFileContent(const char *filename, WiFiClient &client) {
  File file = SD.open(filename);
  if (!file) {
    Serial.println("Error: Couldn't read file!");
  }

  // Lese und sende die Datei schrittweise in kleinen Teilen
  const int bufferSize = 64;
  char buffer[bufferSize];
  while (file.available()) {
    int bytesRead = file.readBytes(buffer, bufferSize);
    client.write(buffer, bytesRead); // Sende den Puffer an den Client
  }

  file.close();
}

String formatDate(String inputDate) {
  // Zerlege den Eingangsstring in Jahr, Monat und Tag
  int year = inputDate.substring(0, 4).toInt();
  int month = inputDate.substring(5, 7).toInt();
  int day = inputDate.substring(8).toInt();

  // Erzeuge einen neuen formatierten String
  String formattedDate = String(day) + "." + String(month) + "." + String(year);

  return formattedDate;
}

String formatTime(String inputTime) {
  // Ersetze %3A durch :
  inputTime.replace("%3A", ":");

  return inputTime;
}
