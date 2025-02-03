#include <Arduino.h>

#include "DCC.h"
#include "Defines.h"
#include "SSD1306Display.h"
#include "InputFunktionen.h"

// Variablen zum Speichern des aktuellen und vorherigen Poti-Werts
int lastPotiValue = 0;  // Anfangswert für den Vergleich
int currentPotiValue = 0;  // Variable für den aktuellen Poti-Wert

int aktuelleLokAdresse = 3;

// Globale Variable für die Geschwindigkeit
int speed = 0;

void ControlSpeed() 
{
  int potiValue = analogRead(POTI_PIN);  // Lese den Poti-Wert (0 bis 4095)
  
  // Mappe den Poti-Wert auf den Bereich -28 bis 28
  int speed;
  if (potiValue > (2048 + deadZone)) 
  {
    speed = map(potiValue, 2048 + deadZone, 4095, 0, 28);
  } 
  else if (potiValue < (2048 - deadZone)) 
  {
    speed = map(potiValue, 0, 2048 - deadZone, -28, 0);
  } 
  else 
  {
    speed = 0; // Innerhalb der Totzone ist die Geschwindigkeit 0
  }

  bool fahrtrichtung;  // Variable für Fahrtrichtung
  bool lokFaehrt = true; // Standardmäßig auf "Lok fährt" setzen

  // Setze die Fahrtrichtung und Geschwindigkeit
  if (speed > 0) 
  {
    // Positive Geschwindigkeit = Rückwärts (Drehen nach rechts)
    fahrtrichtung = false;
  } 
  else if (speed < 0) 
  {
    // Negative Geschwindigkeit = Vorwärts (Drehen nach links)
    fahrtrichtung = true;
    speed = abs(speed);  // Mache die Geschwindigkeit positiv für DCC
  } 
  else 
  {
    // Wenn die Geschwindigkeit 0 ist, Lok steht
    lokFaehrt = false;
  }

  // Sende DCC-Geschwindigkeitsbefehl
  SendeGeschwindigkeit(aktuelleLokAdresse, speed, fahrtrichtung);  // Lok-Adresse, Geschwindigkeit, Fahrtrichtung und Fahrstatus übergeben

  // Debugging-Info (Seriell anzeigen)
  Serial.print("Geschwindigkeit eingestellt auf: ");
  if (!fahrtrichtung) 
  {  // Wenn die Lok rückwärts fährt
    Serial.print(-speed);  // Zeige den speed-Wert als negativ an
  } 
  else 
  { 
    Serial.print(speed);  // Zeige den speed-Wert an
  }
  Serial.print(" | Fahrtrichtung: ");
  Serial.print(fahrtrichtung ? "Vorwärts" : "Rückwärts");
  Serial.print(" | Lok fährt: ");
  Serial.println(lokFaehrt ? "Ja" : "Nein");

  // Display anzeige
  if (!fahrtrichtung) 
  {  // Wenn die Lok rückwärts fährt
    displayPotiValue(-speed);  // Zeige den speed-Wert als negativ an
  } 
  else 
  {
    displayPotiValue(speed);  // Zeige den speed-Wert an
  }
}


// Noch in Bearbeitung 
void ControlFunktion()
{


}
// Noch in Bearbeitung 


bool Befehlaenderungerkannt()
{
  int potiWert = analogRead(POTI_PIN);  // Lese den Poti-Wert (0 bis 4095)
  int mappedWert;

  if (potiWert > (2048 + deadZone)) // Map den Wert auf -28 bis 28
  {
    mappedWert = map(potiWert, 2048 + deadZone, 4095, 0, 28);
  } 
  else if (potiWert < (2048 - deadZone)) 
  {
    mappedWert = map(potiWert, 0, 2048 - deadZone, -28, 0);
  } 
  else 
  {
    mappedWert = 0; // Innerhalb der Totzone auf 0 setzen
  }

  // Steuere die Geschwindigkeit der Lok basierend auf dem Geschwindigkeits-Wert nur, wenn dieser sich geändert hat
  currentPotiValue = mappedWert;  
  
  if (currentPotiValue != lastPotiValue) 
  {  // Prüfe, ob sich der Wert geändert hat
  lastPotiValue = currentPotiValue;  // Aktualisiere den letzten Geschwindigkeits-Wert
   return(true);    // Gibt ein true Zurück um die neue geschwindigkeit zu senden 
  }
  else
  {
    return(false);
  }
}

// in Berabeitung
void AdresseWechseln()
{
  if(aktuelleLokAdresse == 3 && (!digitalRead(SWITCH_PIN) == HIGH))
  {
    aktuelleLokAdresse = 10;
    delay(100);
  }
  else if (aktuelleLokAdresse == 10 && (!digitalRead(SWITCH_PIN) == HIGH))
  {
    aktuelleLokAdresse = 3;
    delay(100);
  }
  else
  {

  }
  display.display();
}
