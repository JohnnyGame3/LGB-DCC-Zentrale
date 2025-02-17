#ifndef DEFINES_H    // Falls DEFINES_H nicht definiert ist...
#define DEFINES_H    // definiere DEFINES_H

#include <Arduino.h>

// Pin belegung
const int RPWM_PIN = 4;       // Aktivierung der H-Brücke für RPWM
const int LPWM_PIN = 5;        // Aktivierung der H-Brücke für LPWM
const int REN_PIN = 6;         // Steuerung der H-Brücke für +24V
const int LEN_PIN = 7;         // Steuerung der H-Brücke für -24V

const int POTI_PIN = 12;        // Pin für das Potentiometer
const int SWITCH_PIN = 15;
const int OLED_SDA_PIN = 20;    // OLED SDA Pin
const int OLED_SCL_PIN = 21;    // OLED SCL PIN


//DCC Timings
const unsigned long Eins_Bit_Zeit = 58;         // 1/2  Timer für High/Low side des 1-Bit
const unsigned long Null_Bit_Zeit = 116;        // 1/2  Timer für High/Low side des 0-Bit
const unsigned long delay_Time = 5;             // Timer für die dead zeit (Verzögerung zwichen dem umschalten der H-Brücke) (MIN 5 !!)
//tconst unsigned long zwichenPaketZeit = 500;    // Zeit zwichen den DCC Paketen (Standard 5ms)

const unsigned long LETZTE_BEFEHLE_WIEDERHOLEN = 500;

const int deadZone = 100; // Größe des Nullbereichs (z.B. +/- 100 um die Mitte)

//Display Größe 
#define SCREEN_HEIGHT 64        // OLED Display Breite
#define SCREEN_WIDTH 128        // OLED Display Höhe

// Wiederholungen
const int SyncBits = 17;        // Bestimmt die Anzahl an Sync-Bits die vor einem Protokoll gesendet werden (Standard 17)
const int Wiederholungen = 5;   // Bestimmt die Anzahl wie oft ein Protokoll Wiederholt wird (Standard 3)

// Modi 
extern bool fahrmodus;          // Muss in Main auf True gesetzt werden um den Fahrmodus (Normalen Modus) zu aktiviren


extern int aktuelleLokAdresse;   // Erstmal nur testweise


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

// Bool Werte zum checken was übergeben wurde
extern bool lok1Neu;
extern bool lok2Neu;
extern bool weicheNeu;

// Werte fpr die "Internen Relais"ä
extern int relais;
extern bool zustandRalais;
extern bool relaisNeu;


// Programmiere Variablen



#endif  // End-Guard: Endet, falls DEFINES_H bereits definiert ist
