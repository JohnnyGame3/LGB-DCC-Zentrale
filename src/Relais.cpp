#include "Relais.h"
#include "Defines.h"

unsigned long vergangeneMillisRelais = 0; // Variable für die vergangene Zeit

void SetupRelais() 
{
    for (int i = 0; i < 4; i++) 
    {
        pinMode(geradePins[i], OUTPUT);
        pinMode(geschaltenPins[i], OUTPUT);
        digitalWrite(geradePins[i], LOW);
        digitalWrite(geschaltenPins[i], LOW);
    }
}

void SchalteRelais() 
{
    if (weicheRelais < 128 || weicheRelais > 131) return;

    int index = weicheRelais - 128;

    if (zustandRalais == false) 
    {
        digitalWrite(geradePins[index], HIGH);
    } 
    else 
    {
        digitalWrite(geschaltenPins[index], HIGH);
    }

    if (millis() - vergangeneMillisRelais >= RelaiAnZeit) 
    {
        vergangeneMillisRelais = millis();
        digitalWrite(geradePins[index], LOW);
        digitalWrite(geschaltenPins[index], LOW);
        relaisNeu = false;
    }
}
