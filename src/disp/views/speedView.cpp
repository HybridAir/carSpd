// class used to display the speedometer view
#include "disp/views/speedView.hpp"


// class constructor, get everything all set up in here
speedView::speedView() {
    // get the initial speed unit from carInput
    lastUpdate = millis();                                                      // get the latest time for the update timer
    currentSpeed = getSpeed();
    prevSpeed = currentSpeed;
    currentUnitMph = getSpeedUnit();
    prevUnit = currentUnitMph;
    dataChanged = true;
}


// call this as often as possible
void speedView::run() {
    betterSpeed();                                                              // test, this should be called outside of this
    monitorButtons();                                                           // check buttons

    uint16_t currentMillis = millis();
    if ((currentMillis - lastUpdate >= UPDATERATE) || updateNow) {              // update every UPDATERATE ms or if updateNow is true
        lastUpdate = currentMillis;
        updateNow = false;

        currentSpeed = getSpeed();                                              // get the current speed and compare it against the previous one

        if(currentSpeed != prevSpeed) {
            prevSpeed = currentSpeed;
            dataChanged = true;
        }

        // get the current speed unit and compare it against the previous one
        currentUnitMph = getSpeedUnit();
        if(currentUnitMph != prevUnit) {
            prevUnit = currentUnitMph;
            dataChanged = true;
        }

        // bypass the display update timer if needed
        if(dataChanged) {
            dataChanged = false;
            updateDisplay();
        }
    }
}


void speedView::monitorButtons() {
    //check all the given buttons for changes
    btn1.read();
    //btn2.read();
    //btn3.read();

    if(btn1.wasPressed()) {
        toggleSpeedUnit();
    }

    // button 1 toggles the speed unit
    // buttons 2 and 3 do nothing yet
    // button 4 is the menu button, and we can't do anything with it here
}


// updates the display with the current speed and unit
void speedView::updateDisplay() {
    drawSpeed();
    drawUnit();
}


// formats and draws the current speed unit to the LCD
void speedView::drawUnit() {
    lcd.setCursor(12, 0);
    if(currentUnitMph) {
        lcd.print(" MPH");
    }
    else {
        lcd.print("KM/H");
    }
}


// formats and draws the current speed to the LCD in big number form
void speedView::drawSpeed() {
    if(currentSpeed == 0) {                                                     // don't need to do anything fancy if the speed is zero
        // clear any possibly still displayed leading numbers (like if the vehicle was decelerating to a stop)
        clearBigNum(-1);
        clearBigNum(3);
        drawBigNum(7, '0');
    }
    else {
        sprintf(speedDigits, "%03d", currentSpeed);                             // put the each digit from the current speed into a char array
        uint8_t places = 0;                                                     // keep track of how many digits are displayed
        for(uint8_t i = 0; i < SPEEDNUMPLACES; i++) {                           // for each possible digit that can be displayed
            if(speedDigits[i] > '0' || places > 0) {                            // make sure not to display any leading zeroes
                drawBigNum((-1 + (i*4)), speedDigits[i]);                       // print out each big number at the right place
                places++;
            }
            else {
                clearBigNum(-1 + (i*4));                                        // chances are the speed decreased enough to create a new leading zero, so remove the old number
            }
        }
    }
}
