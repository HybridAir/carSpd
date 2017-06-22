#ifndef MAIN_H
#define MAIN_H

#include "Arduino.h"
#include <stdint.h>


// carInput public prototypes
void carInit();
void betterSpeed();
void toggleSpeedUnit();
bool getSpeedUnit();
uint8_t getSpeed();
void setSpeedUnit(bool inputUnit);

void displayInit();
void printSpeed(byte speed);
void setContrast(byte contrastInput);
byte incContrast();
byte decContrast();
void setView(byte indexInput);

void initSettings();
void initReadEeprom();
void checkButtons();
void resetEeprom();
void setLightMode(bool modeInput);
void setBrightness(byte newBrightness);

#endif
