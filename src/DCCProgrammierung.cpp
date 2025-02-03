# include <Arduino.h>
#include "DCC.h"
#include "Defines.h"


byte CVByteErstellen(int cv)    // Funktion zum Erstellen des CV-Bytes 
{
  
    if (cv < 1) cv = 1;         // Begrenze CV auf Werte >= 1   
    if (cv> 256) cv = 256;      // Begrenze CV auf Werte <= 256 

    cv = cv - 1;                // Reduziert CV um 1, da CV 1 als 0x00 gesendet wird

    return ((cv & 0b11111111)); // Gibt nur die unteren 8 Bit zurück    
}


byte CVWertByteErstellen(int wert)  // Erstellt ein Byte mit dem zu änderndem wert
{
  
    if (wert < 0) wert = 0 ;        // Begrenze Wert auf 0     
    if (wert> 255) wert = 255;      // Begrenze Wert auf 255 


    return ((wert & 0b11111111));   // Gibt nur die unteren 8 Bit zurück   
}


void SendeRuecksetzBefehl ()            // zum umschalten des Decoders in den Programmiermodus 
{
    byte packet[3];                     // Erstellt ein Themporeres Byte-Array

    packet[0] = 0x00;                   // Broadcast-Adresse
    packet[1] = 0x00;                   // Rücksetz-Byte
    packet[2] = packet[0] ^ packet[1];  // Erstellt ein XOR-Prüfbyte (0x00)

    SendeDCCPaket(packet, 3);           // Sendet das DCC Datenpaket

}


void SendeProgrammierBefehl(int cv, int wert) {
    byte packet[5];  // Temporäres Byte-Array für das DCC-Paket

    packet[0] = 0x03;             // Zieladresse des Decoders (z.B. 3)
    packet[1] = 0xEC;             // Befehl für POM (Programming on Main)

    // CV-Berechnung: CV-Nummer in DCC-Format konvertieren
    packet[2] = ((cv - 1) >> 3) | 0xE0; // Oberste 3 Bits für CV-Bereich (CV-1)
    packet[3] = wert;           // Wert, der in die CV geschrieben werden soll, z.B. 6 für CV29=6

    // Prüfsumme (XOR der Bytes 0 bis 3)
    packet[4] = packet[0] ^ packet[1] ^ packet[2] ^ packet[3];

    // Sende das DCC-Paket
    SendeDCCPaket(packet, 5);
}

