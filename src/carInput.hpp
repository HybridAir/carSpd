#ifndef CARINPUT_HPP
#define CARINPUT_HPP

#include "main.hpp"
#include "disp/views/speedView.hpp"

// speed calc variables
const uint16_t samplePeriod = 1000;                                             // how long to get vss samples for, the longer the more accurate
const uint16_t pulsesPerMile = 4000;                                            // vss pulses per mile, my oldsmobile alero does 4000
const float convertMph = pulsesPerMile/3600;                                    // 3600 seconds in an hour, since miles per *hour*
static uint8_t roundedMph;
static uint8_t previousMph;
static uint8_t speedOut = 0;
static unsigned long lastSpeedTime = 0;
static bool isMph = false;
static bool updateSpeedNow = false;

#endif
