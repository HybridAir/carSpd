//handles all display related tasks
#include "main.h"
#include <Wire.h>
#include <ST7032.h>

ST7032 lcd;

byte contrastValue = 30;

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


void incContrast() {
    if(contrastValue >= 16 && contrastValue < 50) {
        contrastValue += 1;
    }
    lcd.setContrast(contrastValue);
    Serial.println(contrastValue);
}


void decContrast() {
    if(contrastValue > 16 && contrastValue <= 50) {
        contrastValue -= 1;
    }
    lcd.setContrast(contrastValue);
    Serial.println(contrastValue);
}
