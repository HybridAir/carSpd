#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "main.hpp"
#include <Button.h>
#include <EEPROMex.h>
#include <RunningAverage.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// button variables
#define BUTTON1_PIN A1
#define BUTTON2_PIN A2
#define BUTTON3_PIN A3
#define BUTTON4_PIN 4
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 40


#define BACKLIGHT_PIN 11


// default eeprom data array, 5 different values are stored, each using a byte of space
// speedUnit bool, lastViewIndex, contrast, lightMode bool, lightLevel
#define SPEEDUNIT_ADDRESS   0
#define LASTVIEWINDEX_ADDRESS   1
#define CONTRAST_ADDRESS   2
#define LIGHTMODE_ADDRESS   3
#define LIGHTLEVEL_ADDRESS   4
byte defaultEepromVals[6] = {0x00, 0x00, 0x1e, 0x00, 0x00};


#define CONTRASTMAX     48
#define CONTRASTMIN     16

static uint8_t currentView = 0;       // the currently displayed view index


// backlight control variables
static bool autoBacklight = false;                                                      // default to auto backlight control mode
static uint8_t autoSampleInterval = 100;          // car lighting input sample rate
static uint32_t lastLightSampleTime = 0;        // the last time the car lighting input was sampled
static uint8_t currentAvg = 0;
static const uint8_t autoLightMin = 20;
static const uint8_t autoLightMax = 250;

static uint8_t currentBrightness = 255;
static const uint8_t brightnessLevels = 8;
static const uint8_t brightnessLevel[brightnessLevels] = {0, 4, 8, 16, 32, 64, 128, 255};
static uint8_t currentLevel = brightnessLevels - 1;


// temperature sensor variables
static DeviceAddress tempSensorAddress;
static const uint16_t tempInterval = 1000;
static uint32_t lastTempTime = 0;
static float temperatureC = 0;


// prototypes
static void checkButtons();
static void initReadEeprom();
static void resetEeprom();
static void runAutoBacklight();
static void setLightMode(bool modeInput);
static void setBrightness(uint8_t level);
static uint8_t incBrightness();
static uint8_t decBrightness();
static void checkTemp();

#endif
