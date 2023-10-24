#include "MICROSD.h"

void getJsonData(String dataArray[]){
    //open JSON file
    StaticJsonDocument<256> doc;
    File file = SD.open("settings.txt");

    if (file){
        DeserializationError error = deserializeJson(doc, file);

        if(!error){
            //save JSON data in Array
            dataArray[0] = doc["date"].as<String>();
            dataArray[1] = doc["time"].as<String>();
        } else{
            Serial.println("Error reading JSON file!");
        }
        file.close();
    } else{
        Serial.println("Error opening file!");
    }
}

void updateJson(String date, String time){

    StaticJsonDocument<256> doc;
    doc["date"] = date;
    doc["time"] = time;

    File file = SD.open("settings.txt",  O_WRITE);

    if (file){
        
        if (serializeJson(doc, file) == 0){
            Serial.println("Error writing JSON file!");
        } else {
            Serial.println("Written in JSON file!");
        }
        
        file.close();
        
    } else {
        Serial.println("Couldn't open settings.txt!");
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
