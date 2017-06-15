//handles all user control stuff (buttons, settings, eeprom, etc)

#include "main.h"
#include <Button.h>

#define BUTTON1_PIN 6
#define BUTTON2_PIN 7
#define BUTTON3_PIN 8
#define BUTTON4_PIN 9

#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 40

Button btn1(BUTTON1_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn2(BUTTON2_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn3(BUTTON3_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn4(BUTTON4_PIN, PULLUP, INVERT, DEBOUNCE_MS);


void checkButtons() {
    btn1.read();
    btn2.read();
    btn3.read();
    btn4.read();


    if(btn1.wasPressed()) {
        toggleSpeedType();
        printSpeed(getSpeed());
    }

    if(btn2.wasPressed()) {
        incContrast();
    }

    if(btn3.wasPressed()) {
        decContrast();
    }

    if(btn4.isPressed()) {
        digitalWrite(13, HIGH);
    }
    else {
        digitalWrite(13, LOW);
    }
}
