// handles all display related tasks
#include "main.h"
#include <Wire.h>
#include <ST7032.h>

#define CONTRASTMAX     48
#define CONTRASTMIN     16

ST7032 lcd;

byte contrastValue = 30;
byte currentView = 0;       // the currently displayed view index

//initializes the display system
void displayInit() {
    lcd.begin(16, 2);
    lcd.setContrast(contrastValue);
    //get the contrast settings
    //run the boot animation
    Serial.begin(9600);
}


void printSpeed(byte speed) {
    lcd.setCursor(0, 0);
    if(getSpeedType()) {
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
byte incContrast() {
    if(contrastValue >= CONTRASTMIN && contrastValue < CONTRASTMAX) {
        contrastValue += 1;
    }
    lcd.setContrast(contrastValue);
    //Serial.println(contrastValue);

    return contrastValue;
}


// decreases the contrast within the allowed range, and returns the new value
byte decContrast() {
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
