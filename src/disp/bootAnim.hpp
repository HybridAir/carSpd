#ifndef BOOTANIM_HPP
#define BOOTANIM_HPP

#include "main.hpp"
#include "disp/big.hpp"

extern ST7032 lcd;


// custom lcd characters for the logo
static const uint8_t top1[] = {0x1, 0x1, 0x3, 0x3, 0x7, 0x7, 0x3, 0x1};
static const uint8_t top2[] = {0x10, 0x10, 0x18, 0x18, 0x1c, 0x1c, 0x18, 0x10};
static const uint8_t left2[] = {0x18, 0x1c, 0x1e, 0x1e, 0x1e, 0x18, 0x0, 0x0};
static const uint8_t left1[] = {0x0, 0x0, 0x1, 0x3, 0x7, 0xf, 0x1e, 0x0};
static const uint8_t right2[] = {0x3, 0x7, 0xf, 0xf, 0xf, 0x3, 0x0, 0x0};
static const uint8_t right1[] = {0x0, 0x0, 0x10, 0x18, 0x1c, 0x1e, 0xf, 0x0};


// class used to create animations that randomly flicker on and off a set amount of times
// it creates a sort of flicker on effect, inspiration: http://sxo-sxo.tumblr.com/post/140167380273/alex-townsend
class Flicker {
    public:
        uint8_t cycle = 0;          // the current flicker cycle
        uint8_t rand;               // the random amount of times to flicker, determines how many frames the animation lasts
        bool currentState = false;  // whether what is being animated should be displayed or not
        bool finished = false;      // the flicker doesn't run forever you know

        Flicker();                  // sets up the random number generator seed
        bool run();                 // run this each frame of the animation, or whenever you want it to update
};


void playBootAnim();
static void playLogo();
static void playNumbers();
static void flicker(uint8_t x, uint8_t bigNum);

static void logoTop(uint8_t x, uint8_t y);
static void logoLeft(uint8_t x, uint8_t y);
static void logoRight(uint8_t x, uint8_t y);
static void clearLogo(uint8_t x, uint8_t y);


#endif
