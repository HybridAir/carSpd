#ifndef CARINPUT_HPP
#define CARINPUT_HPP

#include "main.hpp"
#include "disp/views/speedView.hpp"

// speed calc variables
const uint16_t samplePeriod = 500;                                             // how long to get vss samples for
const uint16_t pulsesPerMile = 4000;                                            // vss pulses per mile, my oldsmobile alero does 4000
//const float convertMph = (float)pulsesPerMile/3600.0;                                    // 3600 seconds in an hour, since miles per *hour*
const float convertMph = (float)pulsesPerMile/7200.0;                                    // 3600 seconds in an hour, since miles per *hour*
static uint8_t roundedMph;
static uint8_t previousMph;
static uint8_t speedOut = 0;
static unsigned long lastSpeedTime = 0;
static bool isMph = false;
static bool updateSpeedNow = false;
static bool firstRun = true;


static const int numReadings = 8;

static float readings2[numReadings];      // the readings from the analog input
static int readIndex = 0;              // the index of the current reading
static float total = 0;                  // the running total
static float average = 0;                // the average

#endif
