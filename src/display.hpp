#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "main.hpp"
#include <Wire.h>
#include <ST7032.h>

#define CONTRASTMAX     48
#define CONTRASTMIN     16

static uint8_t contrastValue = 30;      // current contrast level
static uint8_t currentView = 0;       // the currently displayed view index

//custom lcd characters for the logo
static const byte top1[] = {0x1, 0x1, 0x3, 0x3, 0x7, 0x7, 0x3, 0x1};
static const byte top2[] = {0x10, 0x10, 0x18, 0x18, 0x1c, 0x1c, 0x18, 0x10};
static const byte left2[] = {0x18, 0x1c, 0x1e, 0x1e, 0x1e, 0x18, 0x0, 0x0};
static const byte left1[] = {0x0, 0x0, 0x1, 0x3, 0x7, 0xf, 0x1e, 0x0};
static const byte right2[] = {0x3, 0x7, 0xf, 0xf, 0xf, 0x3, 0x0, 0x0};
static const byte right1[] = {0x0, 0x0, 0x10, 0x18, 0x1c, 0x1e, 0xf, 0x0};

static void bootAnim();
static void logoTop(byte x, byte y);
static void logoLeft(byte x, byte y);
static void logoRight(byte x, byte y);
static void clearLogo(byte x, byte y);

#endif
