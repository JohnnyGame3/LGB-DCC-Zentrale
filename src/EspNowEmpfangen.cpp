#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>  // Importiere die ArduinoJson-Bibliothek

// id zum checken welche daten empfangen wurden
int id = 1;

// Daten für Lok 1
int lok1 = 3;
int speed1 = 0;
int funktion1 = 0;
bool zustand1 = false;
bool richtung1 = true;
     
// Daten für Lok 2
int lok2 = 0;
int speed2 = 0;
int funktion2 = 0;
bool zustand2 = false;
bool richtung2 = true;

// Daten für Weichen
int weiche = 0;
int funktion3 = 0;
bool zustand3 = false;

// Bool um zu checken ob neue daten erhalten wurden
bool lok1Neu = false;
bool lok2Neu = false;
bool weicheNeu = false;


// Struktur für die empfangenen JSON-Daten
typedef struct struct_message 
{
  char jsonData[100];  // Puffer für JSON-Daten   !! Puffer Angepasst !!
} struct_message;

struct_message receivedData;  // Empfange Struktur


// Callback für das Empfangen von Daten
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len) 
{
  if (len <= sizeof(receivedData.jsonData)) 
  {
    memcpy(receivedData.jsonData, data, len);  // Kopiere die empfangenen Daten in den Puffer
    //Serial.print("Empfangene JSON-Daten: ");
    //Serial.println(receivedData.jsonData );

    // Deserialisieren der JSON-Daten
    JsonDocument doc;  // Korrekte Definition von StaticJsonDocument
    DeserializationError error = deserializeJson(doc, receivedData.jsonData);

    if (!error) 
    {
      id = doc["id"]; // ID der Lok auslesen
      if (id == 1) 
      {
        // Daten für Lok 1
        lok1 = doc["lok"];
        speed1 = doc["speed"];
        funktion1 = doc["funktion"];
        zustand1 = doc["zustand"];
        richtung1 = doc["richtung"];
        
        lok1Neu = true;
      } 
      else if (id == 2) 
      {
        // Daten für Lok 2
        lok2 = doc["lok"];
        speed2 = doc["speed"];
        funktion2 = doc["funktion"];
        zustand2 = doc["zustand"];
        richtung2 = doc["richtung"];

        lok2Neu = true;
      }
      else if (id == 3 || id == 4) // 3 und 4 sind kombiniert
      {
        // Daten für Weiche 
        weiche = doc["weiche"];
        zustand3 = doc["zustand"];

        weicheNeu = true;
      }
      else
      {

      }
    } 
    else 
    {
      //Serial.print(F("Fehler beim Deserialisieren: "));
      //Serial.println(error.f_str());
      return;
    }
  } 
  else 
  {
    //Serial.println("Empfangene Daten überschreiten den Puffer.");
  }
}
