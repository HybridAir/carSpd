// handles all general and low-level display related tasks
#include "disp/display.hpp"

//initializes the display system
void displayInit() {
    //lcd.begin(16, 2);
    lcd.setContrast(contrastValue);


    //lcd.clear();
    delay(200);
    playBootAnim();
    for (;;) {}
}











void printSpeed(byte speed) {
    lcd.setCursor(0, 0);
    if(getSpeedUnit()) {
        lcd.print("current mph:");
    }
    else {
        lcd.print("current kph:");
    }
    lcd.setCursor(0, 1);
    lcd.print(speed);
}


// sets the display contrast to a specified value
void setContrast(byte contrastInput) {

    //make sure you're not going outside the usual limits, even though it should never happen in normal operation
    if(contrastInput > CONTRASTMAX) {
        contrastValue = CONTRASTMAX;
    }
    else if(contrastInput < CONTRASTMIN) {
        contrastValue = CONTRASTMIN;
    }
    else {
        contrastValue = contrastInput;
    }
}


// increases the contrast within the allowed range, and returns the new value
uint8_t incContrast() {
    if(contrastValue >= CONTRASTMIN && contrastValue < CONTRASTMAX) {
        contrastValue += 1;
    }
    lcd.setContrast(contrastValue);
    //Serial.println(contrastValue);

    return contrastValue;
}


// decreases the contrast within the allowed range, and returns the new value
uint8_t decContrast() {
    if(contrastValue > CONTRASTMIN && contrastValue <= CONTRASTMAX) {
        contrastValue -= 1;
    }
    lcd.setContrast(contrastValue);
    //Serial.println(contrastValue);

    return contrastValue;
}


// changed to the currently displayed view to another specified one
// give it the index you want to switch to
void setView(byte indexInput) {
    currentView = indexInput;
    //actually switch the view
}
