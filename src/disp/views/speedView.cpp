// class used to display the speedometer view
#include "disp/views/speedView.hpp"


// class constructor, get everything all set up in here
speedView::speedView() {
    // get the initial speed unit from carInput
    lastUpdate = millis();          // get the latest time for the update timer
}


// call this as often as possible
void speedView::run() {

    monitorButtons();       // check buttons

    uint16_t currentMillis = millis();
    if ((currentMillis - lastUpdate >= UPDATERATE) || updateNow) {     // update every UPDATERATE ms or if updateNow is true
        lastUpdate = currentMillis;
        updateNow = false;

        //currentSpeed = getSpeed();
        currentSpeed = 123;                     // just for testing
        if(currentSpeed != prevSpeed) {
            prevSpeed = currentSpeed;
            dataChanged = true;
        }

        currentUnit = getSpeedUnit();
        if(currentUnit != prevUnit) {
            prevUnit = currentUnit;
            dataChanged = true;
        }

        if(dataChanged) {
            dataChanged = false;
            updateDisplay();
        }
    }
}


void speedView::monitorButtons() {
    //check all the given buttons for changes
    btn1.read();
    btn2.read();
    btn3.read();

    // button 1 toggles the speed unit
    // buttons 2 and 3 do nothing yet
    // button 4 is the menu button, and we can't do anything with it here

    // if any button was pressed, updateNow = true
}


// updates the display with the current speed and unit
void speedView::updateDisplay() {
    // lcd.setCursor(0, 0);
    // if(getSpeedUnit()) {
    //     lcd.print("current mph:");
    // }
    // else {
    //     lcd.print("current kph:");
    // }
    // lcd.setCursor(0, 1);
    // lcd.print(speed);

    drawSpeed();


    // drawBigNum(7, '0');
    // delay(50);
    // lcd.setCursor(12, 0);
    // lcd.print("KM/H");
}


void speedView::drawSpeed() {
    // clear all the numbers
    clearBigNum(-1);
    clearBigNum(3);
    clearBigNum(7);

    if(currentSpeed == 0) {
        drawBigNum(7, '0');
    }
    else {
        sprintf(speedDigits, "%03d", currentSpeed);           // put the each digit from the current speed into a char array
        uint8_t places = 0;
        //lcd.clear();
        for(uint8_t i = 0; i < sizeof(speedDigits); i++) {      // for each possible digit that can be displayed
            //lcd.print(speedDigits[i]);
            if(speedDigits[i] > '0' || places > 0) {          // make sure not to display any leading zeroes
                drawBigNum((-1 + (i*4)), speedDigits[i]);          // print out each big number at the right place
                places++;
            }
        }


        // uint8_t places = 0;
        // uint8_t speedOut = currentSpeed;
        // while(speedOut){
        //   speedOut = speedOut/10;
        //   count++;
        // }
        //
        //
        //
        // do {
        //     uint8_t digit = n % 10;
        //     putchar('0' + digit);
        //     n /= 10;
        //     places++;
        // } while (n > 0);
    }
}
