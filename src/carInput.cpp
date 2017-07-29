// handles all car input and conversion stuff
#include "carInput.hpp"


void carInit() {
    // prepare the VSS input hardware counter thing
    TCCR1A = 0;                                                                 // Configure hardware counter
    TCNT1 = 0;                                                                  // Reset hardware counter to zero
}


// toggles the currently shown speed unit (mph/kph)
void toggleSpeedUnit() {
    if(isMph) {
        isMph = false;
    }
    else {
        isMph = true;
    }
}


// returns the current speed Unit
bool getSpeedUnit() {
    return isMph;
}


// returns the current speed
uint8_t getSpeed() {
    return speedOut;
}


// returns the car's illumination input as an 8-bit value (0-255)
uint8_t getCarBrightness() {
    return map(analogRead(A0), 0, 1023, 0, 255);
}


// calculates the vehicle speed over the last samplePeriod (usually a second), run this often
// it uses timer 1, which is on arduino uno pin 5, connect it to your car's VSS output
void betterSpeed() {

    //sample the speed for samplePeriod, and only calculate after that samplePeriod has elapsed
    if(millis() - lastSpeedTime >= samplePeriod) {
        TCCR1B = 0;                                                             // stop counting VSS pulses
        uint16_t count = TCNT1;                                                 // Store the hardware VSS pulse counter in a variable
        TCNT1 = 0;                                                              // Reset hardware VSS pulse counter to zero

        float mph = (count/convertMph)*10;                                      // Convert pulse count into mph.
        if(!isMph) {
            mph = mph * 1.609;                                                  // and then convert it to kph if necessary
        }
        uint16_t imph = (uint16_t) mph;                                         // Cast to integer. 10x allows retaining 10th of mph resolution.

        uint16_t x = imph / 10;
        uint16_t y = imph % 10;

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

        if((roundedMph - previousMph) > 60) {
            speedOut = previousMph;
        }else{
            speedOut = roundedMph;
        }

        //printSpeed(getSpeed());
        previousMph = roundedMph;                                               // Set previousMph for use in next loop
        lastSpeedTime = millis();
        bitSet(TCCR1B, CS12);                                                   // start counting pulses
        bitSet(TCCR1B, CS11);                                                   // Clock on rising edge
    }
}


// sets the speed unit of measurement to mph or kph
void setSpeedUnit(bool inputUnit) {
    isMph = inputUnit;
    // tell the display to update to the new unit or something here
}
