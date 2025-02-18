#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "DCC.h"
#include "SSD1306Display.h"

unsigned long vergangeneMillis;
unsigned long vergangeneMillisRelais;
 
void setup()
{
  // Initialisiere die serielle Kommunikation
  //Serial.begin(115200);
  SetupH_Bruecke();  // Initialisierung: H-Brücke

  BrueckeDeaktivieren();    // Initialisierung: Brücke deaktivieren

  SetupRelais();  // Initialisierung: Relais

  SetupESPNow();  // Initialisiere ESP-NOW

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
    SchalteRelais(weicheRelais,zustandRalais);  // Schaltet die Relais einer Weiche
    if(millis()- vergangeneMillisRelais >= RELAI_AKTIV_ZEIT)
    {
      vergangeneMillisRelais = millis();

      AlleRelaisAusschalten();
      relaisNeu = false;
    }
  }
}

