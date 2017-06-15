//#include "carInput.h"
#include "main.h"



// VSS variables
const int vssInputPin = 5;                                                      // vss input pin
const int samplePeriod = 1000;                                                  // how long to get vss samples for, the longer the more accurate
const float pulsesPerMile = 4000;                                               // vss pulses per mile, my oldsmobile alero does 4000
const float convertMph = pulsesPerMile/3600;                                    // 3600 seconds in an hour, since miles per *hour*
unsigned int count;
float mph;
unsigned int imph;
int roundedMph;
int previousMph;
int prevCount;

int index = 0;                                                                  // the index of the current reading
int total = 0;                                                                  // the running total
int average = 3;

int speedOut = 0;

bool isMph = false;


unsigned long lastSpeedTime = 0;


void carInit() {
    // prepare the VSS input hardware counter thing
    TCCR1A = 0;                                                                 // Configure hardware counter
    TCNT1 = 0;                                                                  // Reset hardware counter to zero
}



void toggleSpeedType() {
    if(isMph) {
        isMph = false;
    }
    else {
        isMph = true;
    }
}

bool getSpeedType() {
    return isMph;
}

byte getSpeed() {
    return speedOut;
}


//non blocking speed tester
void betterSpeed() {

    //sample the speed for samplePeriod, and only calculate after that samplePeriod has elapsed
    if(millis() - lastSpeedTime >= samplePeriod) {
        TCCR1B = 0;                                                             // stop counting
        count = TCNT1;                                                          // Store the hardware counter in a variable
        TCNT1 = 0;                                                              // Reset hardware counter to zero

        mph = (count/convertMph)*10;                                            // Convert pulse count into mph.
        if(!isMph) {
            mph = mph * 1.609;                                         // Convert pulse count into mph.
        }
        imph = (unsigned int) mph;                                              // Cast to integer. 10x allows retaining 10th of mph resolution.

        int x = imph / 10;
        int y = imph % 10;

        // Round to whole mile per hour
        if(y >= 5) {
            roundedMph = x + 1;
        }else{
            roundedMph = x;
        }

        //If mph is less than 1mph just show 0mph.
        //Readings of 0.9mph or lower are some what erratic and can
        //occasionally be triggered by electrical noise.
        if(x == 0) {
            roundedMph = 0;
        }

        // Don't display mph readings that are more than 50 mph higher than the
        // previous reading because it is probably a spurious reading.
        // Accelerating 60mph in one second is rocketship fast so it is probably
        // not real.
        //lcd.clear();
        //lcd.print("current mph:");

        if((roundedMph - previousMph) > 60) {
            //lcd.setCursor(0, 1);
            //lcd.print(previousMph);
            speedOut = previousMph;
        }else{
            //lcd.setCursor(0, 1);
            //lcd.print(roundedMph);
            speedOut = roundedMph;
        }

        printSpeed(getSpeed());
        previousMph = roundedMph;                                               // Set previousMph for use in next loop
        lastSpeedTime = millis();


        bitSet(TCCR1B, CS12);                                                   // start counting pulses
        bitSet(TCCR1B, CS11);                                                   // Clock on rising edge
    }
}
