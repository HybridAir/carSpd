// handles all display related tasks
#include "display.hpp"

ST7032 lcd;


//initializes the display system
void displayInit() {
    lcd.begin(16, 2);
    lcd.setContrast(contrastValue);
    
    Serial.begin(9600);


    lcd.clear();
    delay(200);
    bootAnim();
}


// plays the boot animation
void bootAnim() {
    lcd.createChar(0, (byte *) top1);
    lcd.createChar(1, (byte *) top2);
    lcd.createChar(2, (byte *) left2);
    lcd.createChar(3, (byte *) left1);
    lcd.createChar(4, (byte *) right2);
    lcd.createChar(5, (byte *) right1);
    // flash top, left, right, then all on for a delay
    // turn all off then flicker on each big number position (888.8 or whatever)
    // when all are on, turn all off, then aftwer a short delay display a 0 in the first position along with all other data


// section 1: logo
    // sequential pulse
    logoTop(7, 0);
    delay(275);
    clearLogo(7, 0);
    delay(100);
	logoLeft(6, 1);
    delay(275);
    clearLogo(6, 1);
    delay(100);
	logoRight(8, 1);
    delay(275);
    clearLogo(8, 1);
    delay(150);
    // sequential display
    logoTop(7, 0);
    delay(75);
    logoLeft(6, 1);
    delay(75);
    logoRight(8, 1);
    delay(750);
    // sequential clear
    clearLogo(7, 0);
    delay(75);
    clearLogo(6, 1);
    delay(75);
	clearLogo(8, 1);
    delay(1000);

// section 2: all number positions

}


void logoTop(byte x, byte y) {
    lcd.setCursor(x, y);
    lcd.write(0);
    lcd.write(1);
}

void logoLeft(byte x, byte y) {
    lcd.setCursor(x, y);
    lcd.write(3);
    lcd.write(2);
}

void logoRight(byte x, byte y) {
    lcd.setCursor(x, y);
    lcd.write(4);
    lcd.write(5);
}

void clearLogo(byte x, byte y) {
    lcd.setCursor(x, y);
    lcd.print("  ");
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
