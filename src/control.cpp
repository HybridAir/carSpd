//handles all user input and control stuff (buttons, settings, eeprom, backlight, etc)

#include "control.hpp"


// init button debounce objects
Button btn1(BUTTON1_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn2(BUTTON2_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn3(BUTTON3_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn4(BUTTON4_PIN, PULLUP, INVERT, DEBOUNCE_MS);


// init
void initSettings() {

    // reset the eeprom to default values if a specific button is held during boot
    btn4.read();
    if(btn4.isPressed()) {
        resetEeprom();                                                          // eeprom init test code
    }
    else {
        initReadEeprom();
    }

    pinMode(BACKLIGHT_PIN, OUTPUT);

}


void monitorIO() {
    checkButtons();
    monitorLighting();
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
        EEPROM.writeByte(LIGHTLEVEL_ADDRESS, incBrightness());                  // set the contrast and save it
        //EEPROM.writeByte(CONTRAST_ADDRESS, incContrast());                      // set the contrast and save it
    }

    if(btn3.wasPressed()) {
        EEPROM.writeByte(LIGHTLEVEL_ADDRESS, decBrightness());                  // set the contrast and save it
        //EEPROM.writeByte(CONTRAST_ADDRESS, decContrast());                      // set the contrast and save it
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


// sets the backlight to a specific brightness level, give it the level index you want (0-7)
void setBrightness(uint8_t level) {
    currentLevel = level;
    analogWrite(BACKLIGHT_PIN, brightnessLevel[currentLevel]);
}


// increses the brightness level by 1, and returns the new level
uint8_t incBrightness() {
    if(currentLevel >= 0 && currentLevel < (brightnessLevels - 1)) {
        currentLevel += 1;
    }
    setBrightness(currentLevel);
    return currentLevel;
}


// decreases the brightness level by 1, and returns the new level
uint8_t decBrightness() {
    if(currentLevel > 0 && currentLevel <= (brightnessLevels - 1)) {
        currentLevel -= 1;
    }
    setBrightness(currentLevel);
    return currentLevel;
}


// monitors the car's lighting input, and controls the display backlight as necessary
// run this often
void monitorLighting() {
    //uint8_t output;

    if(autoBacklight) {                                                         // auto mode
        // if the car lighting is on
            // if the car lighting brightness changed
            // update the backlight brightness
        // else, leave the backlight at full brightness
    }
}


// auto mode, car lights off: backlight is at full brightness
// auto mode, car lights on: backlight dims proportionally with the car's light brightness

// manual mode: 8 static brightness levels
