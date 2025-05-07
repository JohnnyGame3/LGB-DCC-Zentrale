#include "Relais.h"
#include "Defines.h"

unsigned long vergangeneMillisRelais = 0; // Variable für die vergangene Zeit

void SetupRelais() 
{
    for (int i = 0; i < 4; i++) 
    {
        pinMode(geradePins[i], OUTPUT);
        pinMode(geschaltenPins[i], OUTPUT);
        digitalWrite(geradePins[i], HIGH);
        digitalWrite(geschaltenPins[i], HIGH);
    }
}

void SchalteRelais() 
{
    if (weicheRelais < 128 || weicheRelais > 133) return;

    int index = weicheRelais - 129;

    static bool relaisAktiv = false;

    if (!relaisAktiv)
    {
        if (zustandRalais == false) 
        {
            digitalWrite(geradePins[index], LOW);
        } 
        else 
        {
            digitalWrite(geschaltenPins[index], LOW);
        }
        vergangeneMillisRelais = millis();  // Zeit merken
        relaisAktiv = true;
    }
    else if (millis() - vergangeneMillisRelais >= RelaiAnZeit) 
    {
        digitalWrite(geradePins[index], HIGH);
        digitalWrite(geschaltenPins[index], HIGH);
        relaisNeu = false;
        relaisAktiv = false;
    }
}
