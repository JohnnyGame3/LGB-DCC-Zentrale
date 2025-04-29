#ifndef RELAIS_H    // Falls RELAIS_H nicht definiert ist...
#define RELAIS_H    // definiere RELAIS_H

#include <Arduino.h>

void SetupRelais(); // Initialisiere die Relais-Pins
void SchalteRelais();  // Schalte die Relais entsprechend dem Zustand

#endif  // End-Guard: Endet, falls RELAIS_H bereits definiert ist
