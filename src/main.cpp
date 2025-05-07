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

  SetupH_Bruecke(); // Initialisiere die H-Brücke

  SetupRelais();        // Initialisiere die Relais-Pins

  BrueckeDeaktivieren();    // Initialisierung: Brücke deaktivieren

  SetupESPNow(); // Initialisiere ESP-NOW

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