#ifndef ESPNOWEMPFANGEN_H    // Falls DEFINES_H nicht definiert ist...
#define ESPNOWEMPFANGEN_H    // definiere DEFINES_H

#include <Arduino.h>


void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int len);


#endif  // End-Guard: Endet, falls DEFINES_H bereits definiert ist