// carSpd main, currently being tested on an arduino uno
#include "main.h"


void setup() {
    Serial.begin(9600);
    displayInit();
    carInit();
    initSettings();
}


void loop() {
    betterSpeed();
    checkButtons();

}
