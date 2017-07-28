#include "disp/views/speedView.hpp"


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
