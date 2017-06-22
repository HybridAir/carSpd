//handles all user input and control stuff (buttons, settings, eeprom, backlight, etc)

#include "main.hpp"
#include <Button.h>
#include <EEPROMex.h>


// button stuff
#define BUTTON1_PIN 6
#define BUTTON2_PIN 7
#define BUTTON3_PIN 8
#define BUTTON4_PIN 9
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 35

Button btn1(BUTTON1_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn2(BUTTON2_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn3(BUTTON3_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn4(BUTTON4_PIN, PULLUP, INVERT, DEBOUNCE_MS);


// backlight control variables
bool autoBacklight = true;                                                      // default to auto backlight control mode


// default eeprom data array, 5 different values are stored, each using a byte of space
// speedUnit bool, lastViewIndex, contrast, lightMode bool, lightLevel
#define SPEEDUNIT_ADDRESS   0
#define LASTVIEWINDEX_ADDRESS   1
#define CONTRAST_ADDRESS   2
#define LIGHTMODE_ADDRESS   3
#define LIGHTLEVEL_ADDRESS   4
byte defaultEepromVals[6] = {0x00, 0x00, 0x1e, 0x01, 0x00};


void initSettings() {

    // reset the eeprom to default values if a specific button is held during boot
    btn4.read();
    if(btn4.isPressed()) {
        resetEeprom();       // eeprom init test code
    }
    else {
        initReadEeprom();
    }

}


// reads all the settings out from eeprom, and sets initial variables, run at boot
void initReadEeprom() {
    // for each possible stored byte
    for(byte i = 0; i < sizeof(defaultEepromVals); i++) {
        // read each byte into its corresponding function
        switch(i) {
        case SPEEDUNIT_ADDRESS:                                                 // address 0: speed unit (mph/kph), as a bool
            setSpeedUnit(EEPROM.read(i));
            break;
        case LASTVIEWINDEX_ADDRESS:                                             // address 1: last displayed view index number, as a byte
            setView(EEPROM.read(i));
            break;
        case CONTRAST_ADDRESS:                                                  // address 2: display contrast, as a byte
            setContrast(EEPROM.read(i));
            break;
        case LIGHTMODE_ADDRESS:                                                 // address 3: backlight mode (auto/manual), as a bool
            setLightMode(EEPROM.read(i));
            break;
        case LIGHTLEVEL_ADDRESS:                                                //address 4: backlight brightness level, as a byte
            setBrightness(EEPROM.read(i));
            break;
        default:
            break;
        }
    }
}


void checkButtons() {
    btn1.read();
    btn2.read();
    btn3.read();
    btn4.read();


    if(btn1.wasPressed()) {
        toggleSpeedUnit();
        printSpeed(getSpeed());
    }

    if(btn2.wasPressed()) {
        EEPROM.writeByte(CONTRAST_ADDRESS, incContrast());                      // set the contrast and save it
    }

    if(btn3.wasPressed()) {
        EEPROM.writeByte(CONTRAST_ADDRESS, decContrast());                      // set the contrast and save it
    }

    if(btn4.isPressed()) {                                                      // debug code
        digitalWrite(13, HIGH);
    }
    else {
        digitalWrite(13, LOW);
    }
}


// used to write initial default eeprom values
void resetEeprom() {
    for(byte i = 0; i < sizeof(defaultEepromVals); i++) {
        EEPROM.writeByte(i, defaultEepromVals[i]);                              // write each byte in the data value array to the eeprom

        byte output = EEPROM.read(i);                                           // same function as readByte

        Serial.print("adress: ");
        Serial.println(i, DEC);
        Serial.print("input: ");
        Serial.println(defaultEepromVals[i], HEX);
        Serial.print("output: ");
        Serial.println(output, HEX);
        Serial.println("");

    }
}


// sets the current backlight mode to auto or manual, true for auto
void setLightMode(bool modeInput) {
    autoBacklight = modeInput;
}


// sets the backlight to a specific brightness
void setBrightness(byte newBrightness) {
    // just a placeholder right now
}
