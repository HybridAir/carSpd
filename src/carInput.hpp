#ifndef CARINPUT_HPP
#define CARINPUT_HPP

#include "main.hpp"
#include "disp/views/speedView.hpp"

// speed calc variables
const uint16_t samplePeriod = 500;                                              // how long to get vss samples for
const uint16_t pulsesPerMile = 4000;                                            // vss pulses per mile, my oldsmobile alero does 4000
//const float convertMph = (float)pulsesPerMile/3600.0;                                    // 3600 seconds in an hour, since miles per *hour*
const float convertMph = (float)pulsesPerMile/7200.0;                           // 3600 seconds in an hour, since miles per *hour*
static uint8_t roundedMph;
static uint8_t previousMph;
static uint8_t speedOut = 0;
static uint32_t lastSpeedTime = 0;
static bool isMph = false;
static bool updateSpeedNow = false;
static bool firstRun = true;

static volatile bool prevVssState = false;     // tracks the previous vss pin state
static volatile bool recordingVss = false;     // vss pulse time recording state
static volatile uint32_t lastVSSTime = 0;     // the time that the vss pin went high from low
static volatile uint32_t VSSTimeDiff = 0;
static volatile uint32_t VSSPulses = 0;       // used for tracking the number of vss pulses, for distance monitoring and vss pin state changes
static uint32_t prevVssPulses = 0;
static uint32_t lastPulseTime = 0;

#endif
