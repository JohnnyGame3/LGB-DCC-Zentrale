#include "Defines.h"
#include "SSD1306Display.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Erstelle ein SSD1306-Objekt
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Initialisiere das Display
void initDisplay() {
  Wire.begin(OLED_SCL_PIN, OLED_SDA_PIN);  // I2C-Kommunikation starten

  // Initialisiere das OLED-Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {  // Adresse 0x3C für SSD1306
    //Serial.println(F("SSD1306 nicht gefunden!"));
    for (;;);  // Hänge, wenn das Display nicht gefunden wird
  }

  // Display initialisieren
  display.clearDisplay();
  display.setTextSize(1);  // Textgröße auf 1 setzen
  display.setTextColor(SSD1306_WHITE);  // Textfarbe weiß
  display.setCursor(0, 0);
  display.print("Poti-Wert:");
  display.display();  // Aktualisiere das Display
}

// Zeige den Potentiometer-Wert auf dem OLED-Display an
void displayPotiValue(int speedValue) 
{
  display.clearDisplay();  // Lösche das Display
  display.setCursor(0, 0);  // Setze den Cursor auf die Position 0,0
  display.print("Geschw.: ");
  display.println(speedValue);  // Zeige den aktuellen Poti-Wert an
  
  
  display.println(aktuelleLokAdresse); 


  display.display();  // Aktualisiere das Display
  

  // Gib den Poti-Wert zur Überprüfung auch auf der seriellen Konsole aus
  //Serial.print("Poti-Wert auf dem Display: ");
  //Serial.println(speedValue);
}
