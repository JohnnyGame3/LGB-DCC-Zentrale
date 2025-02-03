#ifndef DCCPROGRAMMiERUNG_H     
#define DCCPROGRAMMIERUNG_H     

#include <Arduino.h>

byte CVByteErstellen(int cv);                   // Erstellt ein Byte mit dem CV   
byte CVWertByteErstellen(int wert);             // Erstellt ein Byte mit dem zu änderndem wert


void SendeRuecksetzBefehl ();                   // zum umschalten des Decoders in den Programmiermodus    
void SendeProgrammierBefehl(int CV, int Wert);  // Zum Programmieren über CV´s


#endif  