#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "DCC.h"
#include "SSD1306Display.h"

unsigned long vergangeneMillis;

// Funktion für die erste Loop (Core 0)
void LoopCore0DCC(void *parameter)
{
  while (true)
  {
    /*
    // Leerlaufpaket kontinuierlich senden
    Leerlaufpaket();
    // Regelmäßige Befehlswiederholung
    if (millis() - vergangeneMillis >= LETZTE_BEFEHLE_WIEDERHOLEN) 
    {
      vergangeneMillis = millis();

      WiederholeBefehle(); // Lok- und Funktionsbefehle wiederholen
    }
    if(lok1Neu || lok2Neu || weicheNeu)
    {
      VerarbeiteNeueDaten();  // Liest die neuen daten ein und sendet sie direkt
    }
    else
    {

    }
    vTaskDelay(1);
    */
  }
}
 
// Funktion für die zweite Loop (Core 1)
void LoopCore1ESPNow(void *parameter)
{
  while(true)
  {
    // Leerlaufpaket kontinuierlich senden
    Leerlaufpaket();
    // Regelmäßige Befehlswiederholung
    if (millis() - vergangeneMillis >= LETZTE_BEFEHLE_WIEDERHOLEN) 
    {
      vergangeneMillis = millis();

      WiederholeBefehle(); // Lok- und Funktionsbefehle wiederholen

      /*
      // Ausgabe der deserialisierten Werte
      Serial.print("Empfangene Daten:\n");
      Serial.print("ID: "); Serial.println(id);
      Serial.print("Lok: "); Serial.println(lok1);
      Serial.print("Speed: "); Serial.println(speed1);
      Serial.print("Funktion: "); Serial.println(funktion1);
      Serial.print("Zustand: "); Serial.println(zustand1);
      Serial.print("Richtung: "); Serial.println(richtung1);  
      */
    }
    if(lok1Neu || lok2Neu || weicheNeu)
    {
      VerarbeiteNeueDaten();  // Liest die neuen daten ein und sendet sie direkt
    }
    else
    {

    }
    vTaskDelay(1);
    // Aufgabe für Core 1
  }
}

 
// Hilfsmethode zum Erstellen einer Task
void createTask(void (*taskFunction)(void *), const char *taskName, uint32_t stackSize, uint8_t priority, uint8_t core)
{
  xTaskCreatePinnedToCore(
    taskFunction,   // Zeiger auf die Task-Funktion
    taskName,       // Name der Task
    stackSize,      // Stackgröße in Bytes
    NULL,           // Parameter für die Task (optional)
    priority,       // Priorität der Task
    NULL,           // Task-Handle (nicht verwendet)
    core            // Core, auf dem die Task laufen soll
  );
}
 
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

  pinMode(POTI_PIN,INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  BrueckeDeaktivieren();    // Initialisierung: Brücke deaktivieren
 
  // Tasks erstellen
  createTask(LoopCore0DCC, "TaskCore0", 10000, 1, 0); // Task auf Core 0
  createTask(LoopCore1ESPNow, "TaskCore1", 10000, 1, 1); // Task auf Core 1

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
 
 
void loop()
{
  // Der normale loop()-Code bleibt leer oder wird nur minimal verwendet
}


/*
void loop() 
{ 
  if (fahrmodus == true)
  {        
    Leerlaufpaket();        // Wird gesendet wenn kein Datenbyte übertragen wird 
    if (Befehlaenderungerkannt()==true)   // Erkennt ob es eine änderung in bei der eingabe garb (z.B. Geschwindigkeit hat sich geändert)
    {
      ControlSpeed();       // in InputFunktion deffiniert
      ControlFunktion();    // in InputFunktion deffiniert 
    }   
  }
  else if(fahrmodus == false)   // In Bearbeitung
  {
    delay(10000);
    display.println("delay fertig");
    display.display();
      //SendeRuecksetzBefehl();         // Setzt den Decoder in den Programmiermodus 
      //display.println("rücksetz Gesendet");
      //display.display();
    SendeProgrammierBefehl(29,2);   // 1. Wert = CV (Trage hier das CV ein das du ändern möchtest) 2. Wert = Wert (Trage hier den Wert ein den du im CV ändern möchtest)
    display.println("cv Gesendet");
    display.display();
    delay(99999999);
  } 
}
*/
