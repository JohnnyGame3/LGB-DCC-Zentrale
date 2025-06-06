#ifndef DEFINES_H    // Falls DEFINES_H nicht definiert ist...
#define DEFINES_H    // definiere DEFINES_H

#include <Arduino.h>

// Pin belegung
const int RPWM_PIN = 4;       // Aktivierung der H-Brücke für RPWM
const int LPWM_PIN = 5;        // Aktivierung der H-Brücke für LPWM
const int REN_PIN = 6;         // Steuerung der H-Brücke für +24V
const int LEN_PIN = 7;         // Steuerung der H-Brücke für -24V


const int geradePins[4] = {8, 9, 10, 11};
const int geschaltenPins[4] = {15, 16, 17, 18};

const unsigned long RelaiAnZeit = 300; // Zeit für die Relais (0.3 Sekunde)

//DCC Timings
const unsigned long Eins_Bit_Zeit = 56;         // 1/2  Timer für High/Low side des 1-Bit
const unsigned long Null_Bit_Zeit = 118;        // 1/2  Timer für High/Low side des 0-Bit
const unsigned long delay_Time = 2;             // Timer für die dead zeit (Verzögerung zwichen dem umschalten der H-Brücke) (MIN 5 !!)


const unsigned long LETZTE_BEFEHLE_WIEDERHOLEN = 500;

const int deadZone = 100; // Größe des Nullbereichs (z.B. +/- 100 um die Mitte)

//Display Größe 
#define SCREEN_HEIGHT 64        // OLED Display Breite
#define SCREEN_WIDTH 128        // OLED Display Höhe

// Wiederholungen
const int SyncBits = 17;        // Bestimmt die Anzahl an Sync-Bits die vor einem Protokoll gesendet werden (Min 17)
const int Wiederholungen = 5;   // Bestimmt die Anzahl wie oft ein Protokoll Wiederholt wird (Min 3)

const unsigned long RELAI_AKTIV_ZEIT = 2000; // Zeit in ms, die ads Aktielle Relai Aktiv bleibt

// Werte die mit ESPNow Übergeben werdedn
extern int id;
extern int lok1;
extern int lok2;
extern int speed1;
extern int speed2;
extern bool richtung1;
extern bool richtung2;
extern int funktion1;
extern int funktion2;
extern int funktion3;
extern int weiche;
extern bool zustandLok1;
extern bool zustandLok2;
extern bool zustandWeiche;

// Speichern der Bereits übergebenen funktionen
extern bool lok1Funktionen[13];
extern bool lok2Funktionen[13];

// Bool Werte zum checken was übergeben wurde
extern bool lok1Neu;
extern bool lok2Neu;
extern bool weicheNeu;

// Werte fpr die "Internen Relais"ä
extern int weicheRelais;
extern bool zustandRalais;
extern bool relaisNeu;

// Alte Variablen
const int POTI_PIN = 12;        // Pin für das Potentiometer
//const int SWITCH_PIN = 15;
const int OLED_SDA_PIN = 20;    // OLED SDA Pin
const int OLED_SCL_PIN = 21;    // OLED SCL PIN


//Display Größe 
#define SCREEN_HEIGHT 64        // OLED Display Breite
#define SCREEN_WIDTH 128        // OLED Display Höhe

extern int aktuelleLokAdresse;   // Erstmal nur testweise

//Display Größe 
#define SCREEN_HEIGHT 64        // OLED Display Breite
#define SCREEN_WIDTH 128        // OLED Display Höhe

extern int aktuelleLokAdresse;   // Erstmal nur testweise

#endif  // End-Guard: Endet, falls DEFINES_H bereits definiert ist
