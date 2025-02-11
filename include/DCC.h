#ifndef DCC_H
#define DCC_H

#include <Arduino.h>
#include "Defines.h"
#include "InputFunktionen.h"
#include "DCCProgrammierung.h"
#include "EspNowEmpfangen.h"


// Funktionsprototypen
void DCC_Bit(int microDelay);
void BrueckeDeaktivieren();
void BrueckeAktivieren();
void SendeDCCPaket(byte* packet, int length);
void Leerlaufpaket();

//Programmier Befehl
void NeueDecoderAddresseFestlegen(int address);

//Steuer Befehl
void SendeGeschwindigkeit(int lokAdresse, int speed, bool fahrtrichtung);
void SendeFunktion(int lokAdresse, int funktion, bool Zustand); 
void SendeWeichenFunktion(int weichenAdresse, bool zustand); 

void WiederholeBefehle();
void VerarbeiteNeueDaten();

//Erstellte Bytes
byte LokByteErstellen(int lokAdresse);
byte GeschwByteErstellen(int speed, bool fahrtrichtung);
byte FunktionsByteErstellen(int funktion,bool ein);
byte WeicheByteErstellen(int weichenAdresse); 
byte WeichenFunktionByteErstellen(bool geschaltet);
byte berechneWeichenBytePaket(int adresse, bool schaltzustand, int byteNum); 

#endif // DCC_H
