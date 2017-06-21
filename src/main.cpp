// carSpd main, currently being tested on an arduino uno
#include "main.h"


void setup() {
    Serial.begin(9600);     // used for debug and testing

    initSettings();
    displayInit();
    carInit();
}


void loop() {
    betterSpeed();
    checkButtons();

}
