#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "DCC.h"
#include "SSD1306Display.h"

unsigned long vergangeneMillis;
void setup()
{
  // Initialisiere die serielle Kommunikation
  //Serial.begin(115200);

  //initDisplay();          // Initialisiere das Display
  
  // Konfiguriere alle Pins der BTS7960 als Ausgänge
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);
  pinMode(REN_PIN, OUTPUT);
  pinMode(LEN_PIN, OUTPUT);

  SetupRelais();        // Initialisiere die Relais-Pins

  BrueckeDeaktivieren();    // Initialisierung: Brücke deaktivieren

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

  BrueckeAktivieren();
}
 
 
void loop()
{
  if(lok1Neu || lok2Neu || weicheNeu)
  {
    VerarbeiteNeueDaten();  // Liest die neuen daten ein und sendet sie direkt
  }
  // Regelmäßige Befehlswiederholung
  else if (millis() - vergangeneMillis >= LETZTE_BEFEHLE_WIEDERHOLEN) 
  {
    vergangeneMillis = millis();
  
    WiederholeBefehle(); // Lok- und Funktionsbefehle wiederholen
  }
  else // Leerlaufpaket kontinuierlich senden
  {
    Leerlaufpaket();
  }
  if(relaisNeu)
  {
    SchalteRelais(); // Schalte Relais ein oder aus
  }
}

