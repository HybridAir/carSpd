#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "main.hpp"
#include <Wire.h>
#include "disp/big.hpp"
#include "disp/bootAnim.hpp"

extern ST7032 lcd;

#define CONTRASTMAX     48
#define CONTRASTMIN     16

static uint8_t contrastValue = 30;      // current contrast level
static uint8_t currentView = 0;       // the currently displayed view index






#endif
