#ifndef MAIN_HPP
#define MAIN_HPP

#include "Arduino.h"
#include <stdint.h>
#include <ST7032.h>


// carInput public prototypes
void carInit();
void betterSpeed();
void toggleSpeedUnit();
bool getSpeedUnit();
uint8_t getSpeed();
uint8_t getCarBrightness();
void setSpeedUnit(bool inputUnit);

// display public prototypes
void displayInit();
void displayUpdate();
//void printSpeed(byte speed);
void setContrast(byte contrastInput);
uint8_t incContrast();
uint8_t decContrast();
void setView(byte indexInput);

void controlInit();
void monitorIO();

#endif
