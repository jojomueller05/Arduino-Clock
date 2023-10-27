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
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/html");
    client.println();
    client.println("File not found.");
    return;
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

  // Füge führende Nullen hinzu, wenn der Tag oder Monat einstellig ist
  String formattedDay = (day < 10) ? "0" + String(day) : String(day);
  String formattedMonth = (month < 10) ? "0" + String(month) : String(month);

  // Erzeuge einen neuen formatierten String
  String formattedDate = formattedDay + "." + formattedMonth + "." + String(year);

  return formattedDate;
}



String formatTime(String inputTime) {
  // Ersetze %3A durch :
  inputTime.replace("%3A", ":");

  return inputTime;
}

String incrementDate(String inputDate) {
  // Zerlege den Eingangsstring in Tag, Monat und Jahr
  int day, month, year;
  if (sscanf(inputDate.c_str(), "%d.%d.%d", &day, &month, &year) != 3) {
    // Fehler bei der Konvertierung des Datums
    return "Invalid Date";
  }

  // Ermitteln der Anzahl Tage in jedem Monat
  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Überprüfen, ob das Jahr ein Schaltjahr ist
  bool isLeapYear = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

  // Überprüfen, ob ein Monatswechsel erfolgt
  if (day == daysInMonth[month] && !(month == 2 && day == 29 && isLeapYear)) {
    day = 1;
    month++;
    if (month > 12) {
      month = 1;
      year++;
    }
  } else {
    day++;
  }

  // Erzeuge einen neuen formatierten String
  char formattedDate[11];
  snprintf(formattedDate, sizeof(formattedDate), "%02d.%02d.%04d", day, month, year);

  return String(formattedDate);
}