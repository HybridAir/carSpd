//handles all user input and control stuff (buttons, settings, eeprom, etc)

#include "main.h"
#include <Button.h>
#include <EEPROMex.h>


// button stuff
#define BUTTON1_PIN 6
#define BUTTON2_PIN 7
#define BUTTON3_PIN 8
#define BUTTON4_PIN 9
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 30

Button btn1(BUTTON1_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn2(BUTTON2_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn3(BUTTON3_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn4(BUTTON4_PIN, PULLUP, INVERT, DEBOUNCE_MS);


// eeprom data array, 5 different values are stored, each using a byte of space
// speedUnit bool, lastViewIndex, contrast, lightMode, lightLevel
byte dataValues[6] = {0x00, 0x00, 0x1e, 0x00, 0x00};


void initSettings() {
    //initEepromValues();       // eeprom init test code
}


// used to write initial eeprom values, remove in production
void initEepromValues() {
    for(byte i = 0; i < sizeof(dataValues); i++) {
        EEPROM.writeByte(i, dataValues[i]);   // write each byte in the data value array to the eeprom

        byte output = EEPROM.read(i); // same function as readByte

        Serial.print("adress: ");
        Serial.println(i, DEC);
        Serial.print("input: ");
        Serial.println(dataValues[i], HEX);
        Serial.print("output: ");
        Serial.println(output, HEX);
        Serial.println("");

    }
}


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
