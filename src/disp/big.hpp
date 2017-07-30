#ifndef BIG_HPP
#define BIG_HPP

#include "main.hpp"

extern ST7032 lcd;

static const uint8_t gBigFontShapeTable[] PROGMEM   =   {
    //*      LT[8] =
    B00111,
    B01111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    //*      UB[8] =
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    //*      RT[8] =
    B11100,
    B11110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    //*      LL[8] =
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B01111,
    B00111,
    //*      LB[8] =
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    //*      LR[8] =
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11110,
    B11100,
    //*      UMB[8] =
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    //*      LMB[8] =
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111
};

static const uint8_t gBigFontAsciiTable[] PROGMEM    =   {
    0,  1,  2,  3,  4,  5,                                                      //	0x30	0
    //1,  2,  32, 32, 5,  32,                                                     //	0x31	1
    32, 1,  2,  32, 32, 5,                                                     //	0x31	1
    6,  6,  2,  3,  7,  7,                                                      //	0x32	2
    6,  6,  2,  7,  7,  5,                                                      //	0x33	3
    3,  4,  2,  32, 32, 5,                                                      //	0x34	4
    0,  6,  6,  7,  7,  5,                                                      //	0x35	5
    0,  6,  6,  3,  7,  5,                                                      //	0x36	6
    1,  1,  2,  32, 0,  32,                                                     //	0x37	7
    0,  6,  2,  3,  7,  5,                                                      //	0x38	8
    0,  6,  2,  32, 32, 5,                                                      //	0x39	9
};


uint8_t drawBigNum(int8_t x, uint8_t theChar);
void writeBigNumChars();
void clearBigNum(int8_t x);

#endif
