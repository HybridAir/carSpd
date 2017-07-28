//handles all input and control stuff (buttons, settings, eeprom, backlight, etc)
#include "control.hpp"


// button debounce objects
Button btn1(BUTTON1_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn2(BUTTON2_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn3(BUTTON3_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btn4(BUTTON4_PIN, PULLUP, INVERT, DEBOUNCE_MS);

// car illumination input running average object
RunningAverage backlightAvg(10);

// temperature sensor objects
OneWire oneWire(10);
DallasTemperature tempSensor(&oneWire);


// init
void controlInit() {
    // reset the eeprom to default values if a specific button is held during boot
    btn4.read();
    if(btn4.isPressed()) {
        resetEeprom();
    }
    else {                                                                      // else, get the existing settings out of eeprom
        initReadEeprom();
    }

    pinMode(BACKLIGHT_PIN, OUTPUT);     // set up the backlight output pin

    // prepare the temperature sensor
    tempSensor.begin();
    tempSensor.getAddress(tempSensorAddress, 0);        // find the sensor and get its address
    tempSensor.setResolution(tempSensorAddress, 10);    // use 10-bit resolution (accurate to .25 C)
    tempSensor.setWaitForConversion(false);            // make temperature reading non-blocking
    tempSensor.requestTemperatures();      // get the initial temperature value ready
}


// monitors everything, run this often
void monitorIO() {
    checkButtons();
    runAutoBacklight();
    checkTemp();

}


// reads all the settings out from eeprom, and sets initial variables
void initReadEeprom() {
    for(byte i = 0; i < sizeof(defaultEepromVals); i++) {                       // for each possible stored byte
        // read each byte into its corresponding function
        switch(i) {
            case SPEEDUNIT_ADDRESS:                                             // address 0: speed unit (mph/kph), as a bool
                setSpeedUnit(EEPROM.read(i));
                break;
            case LASTVIEWINDEX_ADDRESS:                                         // address 1: last displayed view index number, as a byte
                setView(EEPROM.read(i));
                break;
            case CONTRAST_ADDRESS:                                              // address 2: display contrast, as a byte
                setContrast(EEPROM.read(i));
                break;
            case LIGHTMODE_ADDRESS:                                             // address 3: backlight mode (auto/manual), as a bool
                setLightMode(EEPROM.read(i));
                break;
            case LIGHTLEVEL_ADDRESS:                                            //address 4: backlight brightness level, as a byte
                setBrightness(EEPROM.read(i));
                break;
            default:
                break;
        }
    }
}


// reads button states and does things as necessary
void checkButtons() {
    btn1.read();
    btn2.read();
    btn3.read();
    btn4.read();


    if(btn1.wasPressed()) {
        toggleSpeedUnit();
        //printSpeed(getSpeed());
    }

    if(btn2.wasPressed()) {
        int out = incBrightness();
        EEPROM.writeByte(LIGHTLEVEL_ADDRESS, out);                  // set the contrast and save it
        //EEPROM.writeByte(CONTRAST_ADDRESS, incContrast());                      // set the contrast and save it
        //Serial.print("up");
        //Serial.println(out);
    }

    if(btn3.wasPressed()) {
        int out = decBrightness();
        EEPROM.writeByte(LIGHTLEVEL_ADDRESS, out);                  // set the contrast and save it
        //EEPROM.writeByte(CONTRAST_ADDRESS, decContrast());                      // set the contrast and save it
        // Serial.print("down");
        // Serial.println(out);
    }

    if(btn4.isPressed()) {                                                      // debug
        digitalWrite(13, HIGH);
    }
    else {
        digitalWrite(13, LOW);
    }
}


// writes initial default eeprom values
void resetEeprom() {
    for(byte i = 0; i < sizeof(defaultEepromVals); i++) {
        EEPROM.updateByte(i, defaultEepromVals[i]);                             // write each byte in the data value array to the eeprom
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
    if(!autoBacklight) {
        currentLevel = level;
        analogWrite(BACKLIGHT_PIN, brightnessLevel[currentLevel]);
    }
}


// increses the brightness level by 1, and returns the new level
uint8_t incBrightness() {
    if(!autoBacklight) {
        if(currentLevel >= 0 && currentLevel < (brightnessLevels - 1)) {
            currentLevel += 1;
        }
        setBrightness(currentLevel);
    }
    return currentLevel;
}


// decreases the brightness level by 1, and returns the new level
uint8_t decBrightness() {
    if(!autoBacklight) {
        if(currentLevel > 0 && currentLevel <= (brightnessLevels - 1)) {
            currentLevel -= 1;
        }
        setBrightness(currentLevel);
    }
    return currentLevel;
}


// monitors the car's lighting input, and updates the display backlight as necessary
void runAutoBacklight() {
    if(autoBacklight) {                                                         // only run if auto mode is active
        if(millis() - lastLightSampleTime >= autoSampleInterval) {              // if it has been autoSampleInterval ms since the last car lighting value update
            backlightAvg.addValue(getCarBrightness());                          // add the new car lighting value to the running average

            uint16_t newAvg = backlightAvg.getAverage();                        // get the new average out
            if(currentAvg != newAvg) {                                          // if the average car lighting value changed
                currentAvg = newAvg;
                uint8_t output = currentAvg;

                if(currentAvg < autoLightMin || currentAvg > autoLightMax) {    // if the car light value is close to the outside limits
                    // set the backlight to fully on
                    // it will be fully on if the car's lighting is off (it's probably daytime, so having it at max will help with glare I think)
                    // or if the car's lighting is at its highest level (which probably wont be a perfect 255 but whatever)
                    output = 255;
                }

                analogWrite(BACKLIGHT_PIN, output);                             // update the backlight
            }

            lastLightSampleTime = millis();                                     // reset the timer
        }
    }
}


// updates a temperature variable every tempInterval ms, non blocking call often
void checkTemp() {
    if(millis() - lastTempTime >= tempInterval) {       // if it has been tempInterval ms since the last temperature check
        temperatureC = tempSensor.getTempC(tempSensorAddress);
        lastTempTime = millis();
        //Serial.println(temperatureC);
        tempSensor.requestTemperatures();
    }
}
