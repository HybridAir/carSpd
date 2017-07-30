#ifndef SPEEDVIEW_HPP
#define SPEEDVIEW_HPP

#include <stdio.h>
#include "main.hpp"
#include "disp/big.hpp"
#include "carInput.hpp"
#include "control.hpp"

#define UPDATERATE 250
#define SPEEDNUMPLACES 3

extern ST7032 lcd;
extern Button btn1;
extern Button btn2;
extern Button btn3;

class speedView {
    public:
        speedView();
        void run();

    private:
        void printSpeed();
        void monitorButtons();
        void updateDisplay();
        void drawSpeed();
        void drawUnit();

        uint8_t currentSpeed = 0;
        uint8_t prevSpeed;
        bool currentUnitMph;
        bool prevUnit;
        uint16_t lastUpdate;
        bool updateNow = false;
        bool dataChanged = true;
        char speedDigits[SPEEDNUMPLACES];
};

#endif
