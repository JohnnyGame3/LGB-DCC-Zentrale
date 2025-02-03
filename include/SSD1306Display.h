#ifndef SSD1306DISPLAY_H
#define SSD1306DISPLAY_H

#include <Adafruit_SSD1306.h>
#include "Defines.h"

// Deklariere das Display-Objekt
extern Adafruit_SSD1306 display;

// Funktionsprototypen
void initDisplay();
void displayPotiValue(int potiValue);

#endif
