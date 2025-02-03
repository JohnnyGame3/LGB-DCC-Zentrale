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
void generatePulse(int state);
void SendeDCCPaket(byte* packet, int length);
void Leerlaufpaket();

//Programmier Befehl
void NeueDecoderAddresseFestlegen(int address);

//Steuer Befehl
void SendeGeschwindigkeit(int lokAdresse, int speed, bool fahrtrichtung);

//Noch in Bearbeitung
void SendeFunktion(int lokAdresse, int speed, bool fahrtrichtung, bool lokFaehrt); 
//Noch in Bearbeitung

void WiederholeBefehle();
void VerarbeiteNeueDaten();

//Erstellte Bytes
byte LokByteErstellen(int lokAdresse);
byte GeschwByteErstellen(int speed, bool fahrtrichtung);
byte FunktionsByteErstellen(int funktion,bool ein);


#endif // DCC_H
