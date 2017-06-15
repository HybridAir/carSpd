#ifndef MAIN_H
#define MAIN_H

#include "Arduino.h"

void carInit();
void speedtest();
void betterSpeed();
void toggleSpeedType();
bool getSpeedType();
byte getSpeed();

void displayInit();
void printSpeed(byte speed);
void incContrast();
void decContrast();

void checkButtons();

#endif
