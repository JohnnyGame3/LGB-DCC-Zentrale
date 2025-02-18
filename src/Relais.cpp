#include "Defines.h"


void AlleRelaisAusschalten()
{
    digitalWrite(RELAI1_IN1, LOW);
    digitalWrite(RELAI1_IN2, LOW);
    digitalWrite(RELAI1_IN3, LOW);
    digitalWrite(RELAI1_IN4, LOW);
    digitalWrite(RELAI2_IN1, LOW);
    digitalWrite(RELAI2_IN2, LOW);
    digitalWrite(RELAI2_IN3, LOW);
    digitalWrite(RELAI2_IN4, LOW);
}

void SetupRelais()
{
    pinMode(RELAI1_IN1, OUTPUT);
    pinMode(RELAI1_IN2, OUTPUT);
    pinMode(RELAI1_IN3, OUTPUT);
    pinMode(RELAI1_IN4, OUTPUT);
    pinMode(RELAI2_IN1, OUTPUT);
    pinMode(RELAI2_IN2, OUTPUT);
    pinMode(RELAI2_IN3, OUTPUT);
    pinMode(RELAI2_IN4, OUTPUT);

    AlleRelaisAusschalten();
}

void SchalteRelais(int weiche,bool zustandWeiche)
{
    if(zustandWeiche)
    {
        switch (weiche)
        {
        case 128:
            digitalWrite(RELAI1_IN1, HIGH);
            break;
        case 129:
            digitalWrite(RELAI1_IN2, HIGH);
            break;
        case 130:
            digitalWrite(RELAI1_IN3, HIGH);
            break;
        case 131:
            digitalWrite(RELAI1_IN4, HIGH);
            break;
        default:
            break;
        }
    }
    else if(!zustandWeiche)
    {
        switch (weiche)
        {
        case 128:
            digitalWrite(RELAI2_IN1, HIGH);
            break;
        case 129:   
            digitalWrite(RELAI2_IN2, HIGH);
            break; 
        case 130:   
            digitalWrite(RELAI2_IN3, HIGH);
            break;
        case 131:
            digitalWrite(RELAI2_IN4, HIGH);
            break;
        default:
            break;
        }
    }
    else
    {

    }
}
