#include "disp/bootAnim.hpp"


// plays the boot animation
void playBootAnim() {
    // flash top, left, right, then all on for a delay
    // turn all off then flicker on each big number position (888.8 or whatever)
    // when all are on, turn all off, then aftwer a short delay display a 0 in the first position along with all other data


    playLogo();
    delay(1000);
    lcd.clear();
    delay(200);
    playNumbers();

}

Flicker::Flicker() {
    randomSeed(analogRead(A0));
    rand = random(1, 4);
    finished = false;
}

bool Flicker::run() {
    if(rand > frame) {
        if(currentState) {
            currentState = false;
            frame++;
        }
        else {
            currentState = true;
        }
    }
    else {
        currentState = true;
        finished = true;
    }
    return currentState;
}




void playNumbers() {
    writeBigNumChars();
    Flicker num0;
    Flicker num1;
    Flicker num2;

    uint16_t previousMillis = 0;
    bool flickering = true;
    uint8_t frame = 0;

    while(flickering) {
        uint16_t currentMillis = millis();

        if (currentMillis - previousMillis >= 50) {
            previousMillis = currentMillis;

            if(num1.run()) {
                drawBigNum(3, '8');
            }
            else {
                clearBigNum(3);
            }

            if(frame > 1) {
                if(num0.run()) {
                    drawBigNum(0, '1');
                }
                else {
                    clearBigNum(0);
                }
            }

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

    delay(500);
    clearBigNum(0);
    clearBigNum(3);
    clearBigNum(7);
    delay(40);
    drawBigNum(7, '0');
    delay(50);
    lcd.setCursor(12, 0);
    lcd.print("KM/H");

}


void playLogo() {
    lcd.createChar(0, (uint8_t *) top1);
    lcd.createChar(1, (uint8_t *) top2);
    lcd.createChar(2, (uint8_t *) left2);
    lcd.createChar(3, (uint8_t *) left1);
    lcd.createChar(4, (uint8_t *) right2);
    lcd.createChar(5, (uint8_t *) right1);

    Flicker title;
    Flicker subtitle;

    bool playing = true;
    uint16_t previousMillis = millis();
    uint8_t frame = 0;

    while(playing) {
        uint16_t currentMillis = millis();

        if (currentMillis - previousMillis >= 25) {
            previousMillis = currentMillis;

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

            if(title.finished && subtitle.finished) {
                playing = false;
            }
        }

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
