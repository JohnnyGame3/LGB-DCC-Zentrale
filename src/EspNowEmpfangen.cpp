#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>  // Importiere die ArduinoJson-Bibliothek

// id zum checken welche daten empfangen wurden
int id = 1;

// Daten für Lok 1
int lok1 = 3;
int speed1 = 0;
int funktion1 = 0;
bool zustandLok1 = false;
bool richtung1 = true;
     
// Daten für Lok 2
int lok2 = 0;
int speed2 = 0;
int funktion2 = 0;
bool zustandLok2 = false;
bool richtung2 = true;

// Daten für Weichen
int weiche = 0;
int funktion3 = 0;
bool zustandWeiche = false;

// Bool um zu checken ob neue daten erhalten wurden
bool lok1Neu = false;
bool lok2Neu = false;
bool weicheNeu = false;

// Daten für Relais
int weicheRelais = 128;
bool zustandRalais = false;
bool relaisNeu = false;

// Array zum Speichern des Funktionsstatus für zwei Loks
bool lok1Funktionen[13] = {false};
bool lok2Funktionen[13] = {false};
int aktuelleLok1 = -1;
int aktuelleLok2 = -1;

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
        int neueLok = doc["lok"];
        
        // Falls sich die Lokadresse geändert hat, Array zurücksetzen
        if (neueLok != aktuelleLok1) 
        {
          memset(lok1Funktionen, false, sizeof(lok1Funktionen));
          aktuelleLok1 = neueLok;
        }
        
        lok1 = neueLok;
        speed1 = doc["speed"];
        funktion1 = doc["funktion"];
        zustandLok1 = doc["zustand"];
        richtung1 = doc["richtung"];
        
        // Funktion im Array setzen
        if (funktion1 >= 0 && funktion1 < 13)
        {
          lok1Funktionen[funktion1] = zustandLok1;
        }
        
        lok1Neu = true;
      } 
      else if (id == 2) 
      {
        // Daten für Lok 2
        int neueLok = doc["lok"];
        
        // Falls sich die Lokadresse geändert hat, Array zurücksetzen
        if (neueLok != aktuelleLok2) 
        {
          memset(lok2Funktionen, false, sizeof(lok2Funktionen));
          aktuelleLok2 = neueLok;
        }
        
        lok2 = neueLok;
        speed2 = doc["speed"];
        funktion2 = doc["funktion"];
        zustandLok2 = doc["zustand"];
        richtung2 = doc["richtung"];
        
        // Funktion im Array setzen
        if (funktion2 >= 0 && funktion2 < 13)
        {
          lok2Funktionen[funktion2] = zustandLok2;
        }
        
        lok2Neu = true;
      }
      else
      {
        
      }
      if (id == 3 || id == 4) // 3 und 4 sind kombiniert
      {
        int tempWeichenAdresse = doc["weiche"];
        if(tempWeichenAdresse <= 127)
        {
        // Daten für Weiche 
        weiche = tempWeichenAdresse;
        zustandWeiche = doc["zustand"];

        weicheNeu = true;
        }
        else if(tempWeichenAdresse <= 136)
        {
          weicheRelais = tempWeichenAdresse;
          zustandRalais = doc["zustand"];

          relaisNeu = true;
        }
        else
        {

        }
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

void SetupESPNow()
{
      // Setze den ESP32 als Wi-Fi Station
      WiFi.mode(WIFI_STA);

      // Initialisiere ESP-NOW
      if (esp_now_init() != ESP_OK) 
      {
        //Serial.println("Fehler beim Initialisieren von ESP-NOW");
        return;
      }
      //Registriere den Callback für das Empfangen von Daten
      esp_now_register_recv_cb(OnDataRecv);
}
