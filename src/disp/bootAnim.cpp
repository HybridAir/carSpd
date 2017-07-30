// handles all boot animation related code
#include "disp/bootAnim.hpp"


// plays the boot animation
void playBootAnim() {
    playLogo();
    delay(1000);
    lcd.clear();
    delay(200);
    playNumbers();
}


// flicker class descriptor
Flicker::Flicker() {
    randomSeed(analogRead(A0));                                                 // get a random seed for the rng
    rand = random(1, 4);                                                        // selected a random number between 1 and 4, this determines the flicker amount/duration
}


// updates the flicker animation, returns the current state
// the returned state is used to determine whether you need to display or clear whatever you're trying to flicker
bool Flicker::run() {
    if(rand > cycle) {                                                          // only animate up to the random flicker amount we got before
        if(currentState) {
            currentState = false;
            cycle++;                                                            // advance the cycle value after each complete on/off cycle
        }
        else {
            currentState = true;
        }
    }
    else {
        currentState = true;                                                    // the flicker animation finishes with the animated thing being displayed
        finished = true;
    }
    return currentState;
}


// the first part of the boot animation, displays the logo and the device info
void playLogo() {

    // load the custom logo characters into the lcd's cgram
    lcd.createChar(0, (uint8_t *) top1);
    lcd.createChar(1, (uint8_t *) top2);
    lcd.createChar(2, (uint8_t *) left2);
    lcd.createChar(3, (uint8_t *) left1);
    lcd.createChar(4, (uint8_t *) right2);
    lcd.createChar(5, (uint8_t *) right1);

    // create a flicker class for each title/subtitle
    Flicker title;
    Flicker subtitle;

    // set up the animation timing variables
    bool playing = true;
    uint16_t previousMillis = millis();
    uint8_t frame = 0;

    // the entire animation is controlled in here
    while(playing) {
        uint16_t currentMillis = millis();

        if (currentMillis - previousMillis >= 25) {     // display is updated every 25 ms
            previousMillis = currentMillis;

            // after frame 50, animate the title and subtitle
            if(frame > 50) {
                if((frame % 2) == 0) {
                    if(title.run()) {
                        lcd.setCursor(5, 0);
                        lcd.print("carSpd v0.1");
                    }
                    else {
                        lcd.setCursor(5, 0);
                        for(uint8_t i = 0; i < 11; i++) {
                            lcd.print(" ");
                        }
                    }

                    if(subtitle.run()) {
                        lcd.setCursor(7, 1);
                        lcd.print("HybridAir");
                    }
                    else {
                        lcd.setCursor(7, 1);
                        for(uint8_t i = 0; i < 9; i++) {
                            lcd.print(" ");
                        }
                    }
                }
            }
            frame++;

            if(title.finished && subtitle.finished) {       // the title and subtitle are the last elements to be animated in this section
                playing = false;        // this section of the boot animation is considered to be complete
            }
        }

        // animate the logo
        switch(frame) {
            case 0:
                logoTop(1, 0);
                break;
            case 12:
                clearLogo(1, 0);
                break;
            case 16:
                logoLeft(0, 1);
                break;
            case 28:
                clearLogo(0, 1);
                break;
            case 32:
                logoRight(2, 1);
                break;
            case 44:
                clearLogo(2, 1);
                break;
            case 50:
                logoTop(1, 0);
                break;
            case 53:
                logoLeft(0, 1);
                break;
            case 56:
                logoRight(2, 1);
                break;
        }
    }
}


void logoTop(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
    lcd.write(0);
    lcd.write(1);
}

void logoLeft(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
    lcd.write(3);
    lcd.write(2);
}

void logoRight(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
    lcd.write(4);
    lcd.write(5);
}

void clearLogo(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
    lcd.print("  ");
}


// plays the speedometer number part of the animation
void playNumbers() {
    writeBigNumChars();         // put the custom big number characters into the lcd's cgram

    // create a flicker class for each number position
    Flicker num0;
    Flicker num1;
    Flicker num2;

    // set up the animation timing variables
    uint16_t previousMillis = 0;
    bool flickering = true;
    uint8_t frame = 0;

    // the flickering part of the animation
    // each number position is flickered on in a 2-1-3 order
    // 188 is used to give the illusion of a segmented display defaulting to all segments lit or something idk
    while(flickering) {
        uint16_t currentMillis = millis();

        if (currentMillis - previousMillis >= 50) {         // update the display every 50 ms
            previousMillis = currentMillis;

            // run the second position flicker
            if(num1.run()) {
                drawBigNum(3, '8');
            }
            else {
                clearBigNum(3);
            }

            // run the first position flicker starting at frame 1
            if(frame > 1) {
                if(num0.run()) {
                    drawBigNum(-1, '1');
                }
                else {
                    clearBigNum(-1);
                }
            }

            // run the third position flicker starting at frame 4
            if(frame > 4) {
                if(num2.run()) {
                    drawBigNum(7, '8');
                }
                else {
                    clearBigNum(7);
                }
            }

            frame++;
            if(num0.finished && num1.finished && num2.finished) {
                flickering = false;
            }
        }
    }

    // the second part, transitioning to the final speedometer display
    delay(500);
    clearBigNum(-1);
    clearBigNum(3);
    clearBigNum(7);
    delay(40);
    // drawBigNum(7, '0');
    // delay(50);
    // lcd.setCursor(12, 0);
    // lcd.print("KM/H");
}
