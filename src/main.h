#ifndef MAIN_H
#define MAIN_H

#include "Arduino.h"

void carInit();
void speedtest();
void betterSpeed();
void toggleSpeedType();
bool getSpeedType();
byte getSpeed();
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
void initEepromValues();
void setLightMode(bool modeInput);
void setBrightness(byte newBrightness);

#endif
