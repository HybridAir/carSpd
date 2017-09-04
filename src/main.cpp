// carSpd main, currently being tested on an arduino uno
#include "main.hpp"

ST7032 lcd;

void setup() {
    Serial.begin(9600);     // used for debug and testing
Serial.println("starting");
    lcd.begin(16, 2);

    lcd.clear();
    controlInit();
    displayInit();
    carInit();
}


void loop() {
    //betterSpeed();
    monitorIO();
    displayUpdate();
}
