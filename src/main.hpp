#ifndef MAIN_HPP
#define MAIN_HPP

#include "Arduino.h"
#include <stdint.h>


// carInput public prototypes
void carInit();
void betterSpeed();
void toggleSpeedUnit();
bool getSpeedUnit();
uint8_t getSpeed();
void setSpeedUnit(bool inputUnit);

// display public prototypes
void displayInit();
void printSpeed(byte speed);
void setContrast(byte contrastInput);
unit8_t incContrast();
unit8_t decContrast();
void setView(byte indexInput);

void initSettings();
void initReadEeprom();
void checkButtons();
void resetEeprom();
void setLightMode(bool modeInput);
void setBrightness(byte newBrightness);

#endif
