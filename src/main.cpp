// carSpd main, currently being tested on an arduino uno
#include "main.hpp"


void setup() {
    Serial.begin(9600);     // used for debug and testing

    controlInit();
    displayInit();
    carInit();
}


void loop() {
    betterSpeed();
    //checkButtons();
    monitorIO();
}
