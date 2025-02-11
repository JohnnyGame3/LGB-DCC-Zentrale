#include <Arduino.h>
#include "DCC.h"
#include "Defines.h"

unsigned long Eins = 58;

//unsigned long vergangeneMillis = 0; // Global oder statisch definieren
const long interval = 6; // Wartezeit von 5 ms


// Für zeit steuerung 
unsigned long previousMicros = 0;
bool highPhase = true;

// Deaktiviert beide Seiten der H-Brücke
void BrueckeDeaktivieren() 
{
  digitalWrite(RPWM_PIN, LOW);  // Setzt PWM Rechts auf 0 
  digitalWrite(REN_PIN, LOW);   // Deaktiviere rechte Seite
  digitalWrite(LPWM_PIN, LOW);  // Setzt PWM Links auf 0 
  digitalWrite(LEN_PIN, LOW);   // Deaktiviere linke Seite
}

// Deaktiviert beide Seiten der H-Brücke
void BrueckeAktivieren() 
{
  digitalWrite(REN_PIN, HIGH);   // Aktiviere rechte Seite
  digitalWrite(LEN_PIN, HIGH);   // Aktiviere linke Seite
}

// Methode die die Bits über die H-brücke senden (Die Bit-Zeit muss angegeben werden) 
void DCC_Bit(int microDelay)
{
  BrueckeAktivieren();
  // sendet das 1-Bit (58 µs HIGH, 58 µs LOW)
  //High phase 
  digitalWrite(LPWM_PIN, LOW);      // Setzt PWM Links auf 0 
  delayMicroseconds(delay_Time);    // Tot zeit um der brücke zeit zum schalten zu geben 
  digitalWrite(RPWM_PIN, HIGH);     // Setzt PWM Rechts auf 255(Max) (+24V)
  delayMicroseconds(microDelay);    //High-Phase
 

  // Low Phase
  digitalWrite(RPWM_PIN, LOW);       // Setzt PWM Rechts auf 0 
  delayMicroseconds(delay_Time);     // Tot zeit um der brücke zeit zum schalten zu geben 
  digitalWrite(LPWM_PIN, HIGH);      // Setzt PWM Links auf 255(Max) (-24V)
  delayMicroseconds(microDelay);     // LOW-Phase
}


// Funktion zum Erstellen des Adress-Bytes für die Lok
byte LokByteErstellen(int lokAdresse)
{
  // Begrenze die Adresse auf 1 bis 127
  if (lokAdresse < 1) lokAdresse = 1;     // Mindestadresse ist 1
  if (lokAdresse > 127) lokAdresse = 127; // Höchstadresse ist 127

  // Setze das Adressbyte (Bit 7 ist 0 für Kurzadresse, Bit 6 ist 1 für Adressbefehl)
  return ((lokAdresse & 0b01111111));     // ((0b11000000 | Bit 7 = 0, Bit 6 = 1)), Bits 5-1 = Lokadresse
}


// Funktion zum Erstellen des Befehls-Bytes für die Geschwindigkeitssteuerung
byte GeschwByteErstellen(int speed, bool fahrtrichtung) 
{
  // Temporäres Befehls-Byte mit Bit 1 fest auf 1 und Platz für Richtung und Geschwindigkeit
  byte command = 0b01000000;

  // Geschwindigkeitsbits gemäß Tabelle
  const byte geschwBits[] = 
  {
      0b00000, 0b00010, 0b10010, 0b00011, 0b10011, 0b00100, 0b10100,
      0b00101, 0b10101, 0b00110, 0b10110, 0b00111, 0b10111, 0b01000,
      0b11000, 0b01001, 0b11001, 0b01010, 0b11010, 0b01011, 0b11011,
      0b01100, 0b11100, 0b01101, 0b11101, 0b01110, 0b11110, 0b01111, 0b11111
  };

  // Prüfe, ob Not-Halt aktiviert werden soll
  if (speed == -1) 
  {
    command |= 0b00000001;   // Not-Halt, spezielles Bitmuster für Notstopp
    return command;
  }

  // Begrenze die Geschwindigkeit auf 0 bis 28, falls sie außerhalb dieses Bereichs liegt
  if (speed < 0) speed = 0;
  if (speed > 28) speed = 28;

  // Setze Fahrtrichtung: 1 für vorwärts, 0 für rückwärts
  if (fahrtrichtung) 
  {
    command |= 0b00100000; // Bit 6 für Vorwärts
  }

  // Füge Geschwindigkeitsbits hinzu
  command |= geschwBits[speed]; 

  return command;
}

// Funktion Zum Erstellen Eines FunktionsBytes (Noch sind nur Einfache Verfügbar)
byte FunktionsByteErstellen(int funktion,bool ein)
{

  byte command = 0;           // Erstellt ein Temporeres Befehls-Byte
  int an = ein ? 1 : 0;       // Direkte Zuweisung basierend auf dem booleschen Wert

 
  switch (funktion)           // Erstellt das Byte für die jeweilige Funktion und Zustand
  {
    case 0:
      command = 0b10000000 | (an << 4);  // Setze Bitmuster 0b10000000 und Bit 4 F0
      break;
    case 1:
      command = 0b10000000 | (an << 0);  // Setze Bitmuster 0b10000000 und Bit 0 F1
      break;
    case 2:
      command = 0b10000000 | (an << 1);  // Setze Bitmuster 0b10000000 und Bit 1 F2
      break;
    case 3:
      command = 0b10000000 | (an << 2);  // Setze Bitmuster 0b10000000 und Bit 2 F3
      break;
    case 4:
      command = 0b10000000 | (an << 3);  // Setze Bitmuster 0b10000000 und Bit 3 F4
      break;
    case 5:
      command = 0b10110000 | (an << 0);  // Setze Bitmuster 0b10110000 und Bit 0 F5
      break;
    case 6:
      command = 0b10110000 | (an << 1);  // Setze Bitmuster 0b10110000 und Bit 1 F6
      break;
    case 7:
      command = 0b10110000 | (an << 2);  // Setze Bitmuster 0b10110000 und Bit 2 F7
      break;
    case 8:
      command = 0b10110000 | (an << 3);  // Setze Bitmuster 0b10110000 und Bit 3 F8
      break;
    case 9:
      command = 0b10100000 | (an << 0);  // Setze Bitmuster 0b10100000 und Bit 4 F9
      break;
    case 10:
      command = 0b10100000 | (an << 1);  // Setze Bitmuster 0b10100000 und Bit 0 F10
      break;
    case 11:
      command = 0b10100000 | (an << 2);  // Setze Bitmuster 0b10100000 und Bit 1 F11
      break;
    case 12:
      command = 0b10100000 | (an << 3);  // Setze Bitmuster 0b10100000 und Bit 1 F12
      break;
  } 
  return command;     // Rückgabe des Befehls-Bytes
}
  

// Funktion zum Erstellen des Adress-Bytes für die Weiche
byte WeicheByteErstellen(int weichenAdresse) 
{
  // Begrenze die Adresse auf den gültigen Bereich (1 bis 127)
  if (weichenAdresse < 1) weichenAdresse = 1;
  if (weichenAdresse > 127) weichenAdresse = 127;

  // Setze das Adressbyte (Bit 7 = 0 für Kurzadresse, Bit 6 = 1 für Adressbefehl)
  return (0b11000000 | (weichenAdresse & 0b00111111));
}

// Funktion zum Erstellen des Funktionsbytes für die Weiche
byte WeichenFunktionByteErstellen(bool geschaltet) 
{
  byte command = 0b11111000;  // Standardbefehl für Weichen (immer aktiv)

  if (geschaltet) {
      command |= 0b00000001;  // Schalte die Weiche um (Bit 0 setzen)
  } else {
      command &= 0b11111110;  // Setze Weiche auf "gerade" (Bit 0 löschen)
  }

  return command;
}

// Methode zum Berechnen eines DCC-Pakets für eine Weiche (Ein-Byte-Version)
// Adresse: Adresse des Zubehördecoders (z.B. 1 für Adresse 4)
// Schaltzustand: 0 für Abzweig (links), 1 für Gerade (rechts)
// byteNum: 1 für erstes Byte, 2 für zweites Byte
byte berechneWeichenBytePaket(int adresse, bool schaltzustand, int byteNum) 
{
  // Berechnung der 11-Bit-Adresse (wir verwenden hier die lineare Adresse)
  // Die Adresse wird auf die interne Adresse des Decoders abgebildet (Adresse 1 -> interne Adresse 4)
  int interneAdresse = adresse + 3;  // Adresse 1 entspricht interner Adresse 4

  byte result = 0;

  if (byteNum == 1) {
      // Setzen des ersten Bytes: 1000 0001
      result = (0b10000000 | (interneAdresse >> 3));  // 7 höchste Bits der Adresse
  }
  else if (byteNum == 2) {
      // Setzen des zweiten Bytes: 1111 D00R
      result = (0b11110000 | ((interneAdresse & 0b00000111) << 2));  // 3 niederwertigste Bits der Adresse

      // Setzen des Schaltzustands: D = 1 für Aktivierung, R = 0 für Abzweig / R = 1 für Gerade
      result |= (schaltzustand << 1);  // Setzen von R für Gerade (rechts)
      result |= (1 << 3);  // D = 1 für Aktivierung der Weiche
  }

  return result;
}


// Funktion zum Senden eines DCC-Pakets für Geschwindigkeit
void SendeGeschwindigkeit(int lokAdresse, int speed, bool fahrtrichtung) 
{
    byte packet[3];

    // Erstelle das Adressbyte für die gegebene Lokadresse
    //packet[0] = 0x00; // Für Kurzadressen kann das erste Byte 0 sein
    packet[0] = LokByteErstellen(lokAdresse);               // Erstelle das Adressbyte
    packet[1] = GeschwByteErstellen(speed, fahrtrichtung);  // Erstellt Geschwindigkeitsbyte
    packet[2] = packet[0] ^ packet[1];                      // XOR-Prüfziffer berechnen

    // Sende das DCC-Paket
    SendeDCCPaket(packet, 3);
}


// Funktion zum Senden eines DCC-Pakets für Geschwindigkeit
void SendeFunktion(int lokAdresse, int funktion, bool Zustand) 
{
    byte packet[3];

    // Erstelle das Adressbyte für die gegebene Lokadresse
    //packet[0] = 0x00; // Für Kurzadressen kann das erste Byte 0 sein
    packet[0] = LokByteErstellen(lokAdresse);               // Erstelle das Adressbyte
    packet[1] = FunktionsByteErstellen(funktion, Zustand);  // Erstellt Funktionsbyte
    packet[2] = packet[0] ^ packet[1];                      // XOR-Prüfziffer berechnen

    // Sende das DCC-Paket
    SendeDCCPaket(packet, 3);
}

// Funktion zum Senden eines DCC-Pakets für Geschwindigkeit
void SendeWeichenFunktion(int weichenAdresse, bool zustand) 
{
  byte packet[3];

  // Erstelle das Adressbyte für die gegebene Lokadresse
  //packet[0] = 0x00; // Für Kurzadressen kann das erste Byte 0 sein
  packet[0] = berechneWeichenBytePaket(weichenAdresse, zustand, 1); // Berechne das erste Byte des DCC-Pakets für die Weiche
  packet[1] = berechneWeichenBytePaket(weichenAdresse, zustand, 2); // Berechne das zweite Byte des DCC-Pakets für die Weiche
  packet[2] = packet[0] ^ packet[1];                      // XOR-Prüfziffer berechnen

  // Sende das DCC-Paket
  SendeDCCPaket(packet, 3);
}



void SendeDCCPaket(byte* packet, int length) // Funktion zum Senden eines DCC-Pakets  (Übergane Paket Array, Bits im Paket)
{

  for(int w = 0; w < Wiederholungen; w++)    // Sendet das Gesamte Paket 3 Mal
  {

  //if ((millis() - vergangeneMillis) >= interval) 
  //{

    for (int sb = 0;sb < SyncBits; sb ++)    // Sendet 17 Syncronisation´s 1-Bits 
    {
      DCC_Bit(Eins_Bit_Zeit);     // 1-Bit
    }
  
    for (int i = 0; i < length; i++)            // Durchlaufe alle Bytes im Paket
    {
      DCC_Bit(Null_Bit_Zeit);  // Sende das Startbit vor jedem Byte

      byte data = packet[i];

      for (int bitMask = 0x80; bitMask > 0; bitMask >>= 1) // Sende jedes Bit (MSB zuerst)
      {
        if (data & bitMask) 
        {
          DCC_Bit(Eins_Bit_Zeit); // Sende eine "1"
        } 
        else 
        {
          DCC_Bit(Null_Bit_Zeit); // Sende eine "0"
        }
      }
    }

    DCC_Bit(Eins_Bit_Zeit);                      // Ende-Bit Markiert das ende des Paketes

    //delayMicroseconds(zwichenPaketZeit);    // Zeit zwichen den einzelnden dcc Paketen
    
    //vergangeneMillis = millis(); // Aktuelle Zeit speichern
  
  //}

  }
}


void Leerlaufpaket()                // Sendet ein Leerlaufpaket wenn kein datenpaket übertragen wird 
{
  //Serial.println("Sende Leerlaif paket");

  //if ((millis() - vergangeneMillis) >= interval) 
  //{

    for(int sb = 0; sb < SyncBits; sb++ )   // Sendet 17 Syncronisation´s 1-Bits 
    {
      DCC_Bit(Eins_Bit_Zeit);                     // 1-Bit
    }

    DCC_Bit(Null_Bit_Zeit);                       // 0-Bit (Paket Start-bit)

    for(int ab = 0; ab < 8; ab++)     // Sendet 8x 1-bit (Adress-byte) 
    {
      DCC_Bit(Eins_Bit_Zeit);                     // 1-Bit
    }

    for(int bb = 0; bb < 10; bb++)    // Sendet DartenStratbit + 8x 0-bit (Befehls-byte) + DartenStartbit
    {
      DCC_Bit(Null_Bit_Zeit);                     // 0-Bit
    }

    for(int pb = 0; pb < 8; pb++)     // Sendet 8x 1-bit (Prüf-byte)
    {
      DCC_Bit(Eins_Bit_Zeit);
    }   

    DCC_Bit(Eins_Bit_Zeit);                       // Ende-Bit Markiert das ende des Paketes

    //vergangeneMillis = millis();      // Aktuelle Zeit speichern

    //delayMicroseconds(zwichenPaketZeit);
  //}

}


// Sende gespeicherte Befehle erneut
void WiederholeBefehle() 
{
  SendeGeschwindigkeit(lok1, speed1, richtung1);
  SendeFunktion(lok1, funktion1, zustand1);
  SendeGeschwindigkeit(lok2, speed2, richtung2);
  SendeFunktion(lok2, funktion2, zustand2);
  //Serial.println("Wiederholungs Befehl");
}

// Verarbeite die neu empfangenen Daten
void VerarbeiteNeueDaten() 
{
  //Serial.println("Verarbeite neue Daten");
  if(lok1Neu)
  {
    SendeGeschwindigkeit(lok1, speed1, richtung1);
    SendeFunktion(lok1, funktion1, zustand1);
    lok1Neu = false;
    //Serial.print("Lok 1 neu erhalten und gesendet");
  }
  if(lok2Neu)
  {
    SendeGeschwindigkeit(lok2, speed2, richtung2);
    SendeFunktion(lok2, funktion2, zustand2);
    lok2Neu = false;  
  }
  if(weicheNeu)
  {
    if(weiche <= 128)
    {
      SendeWeichenFunktion(weiche, zustand3);
    }
    else
    {
      // Methoder für die Ralais der Zenterale
    }
    weicheNeu = false;
  }
  else
  {

  }
}

