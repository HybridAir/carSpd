
#include "main.h"


void setup() {
    displayInit();
    carInit();

    pinMode(13, OUTPUT);                                                        // set pin to input
}


void loop() {
    betterSpeed();
    checkButtons();

}
//sdrtdfhfghdf
