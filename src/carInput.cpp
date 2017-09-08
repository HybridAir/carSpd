// handles all car input and conversion stuff
#include "carInput.hpp"


void carInit() {

    pinMode(5, INPUT);                                                          // set pin to input

    // enable pin change interrupt on pcint2
    // pcint2 because that's where pin PD5, the vss pin, lives
    PCICR |= (1<<PCIE2);
    PCMSK2 |= (1<<PCINT21);
}



ISR(PCINT2_vect) {

    bool currentVssState = PIND & _BV(PD5);                                     // get the current state of the vss pin

    if (currentVssState && !prevVssState) {                                     // if the vss pin is high, and was previously low
        if(!recordingVss) {                                                     // if the vss pulse time is not yet being recorded
            // this means that a new vss pulse was just recieved, and needs to be timed
            lastVSSTime = micros();                                             // record the time the vss pin just now went high
            recordingVss = true;                                                // we are recording this vss pulse time now
        }
        else {                                                                  // if the vss pusle time is currently being recorded
            // this means that the vss pin was just pulsed, signalling the end of the previous vss pulse
            VSSTimeDiff = micros() - lastVSSTime;                               // subtract the current time by the time the last vss pulse started, this gets you the duration of the last vss pulse
            VSSPulses++;
            recordingVss = false;                                               // we are finally done recording the last vss pulse time
        }
    }


    prevVssState = currentVssState;

}


// toggles the currently shown speed unit (mph/kph)
void toggleSpeedUnit() {
    if(isMph) {
        isMph = false;
    }
    else {
        isMph = true;
    }

    updateSpeedNow = true;
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


// calculates the vehicle speed using the data gathered over the past samplePeriod (500ms recommended)
// it uses timer 1 on arduino uno pin 5, connect it to your car's VSS signal line
void betterSpeed() {

    if (VSSPulses != prevVssPulses) {                                           // if the vss pulse count just changed
        // that means a new vss pulse time was just recorded
        // go use it to calculate the vehicle's current speed
        prevVssPulses = VSSPulses;                                              // record the new vss pulse count

        uint32_t speed = 1000000000 / (VSSTimeDiff/10);
        //float div = 4000.0/3600;
        float div = (pulsesPerMile*1000.0)/3600;                                // the amount of vss pulses in one second, with 5 "decimals" of accuracy
        uint16_t mph = speed / (uint16_t)div;

        if(!isMph) {                                                            // convert to kph if needed
            mph = mph * 1.6093;
        }

        uint16_t x = mph / 10;                                                  //remove the "decimal"
        uint16_t y = mph % 10;                                                  //check the "decimal" to see if the output needs rounding

        // Round to whole mile per hour
        if(y >= 5) {                                                            //if the "decimal" (the 9 in 659) is greater/equal to 5, round up
            roundedMph = x + 1;
        }else{
            roundedMph = x;
        }

        speedOut = roundedMph;                                                  // done, that's the final speed
        lastPulseTime = millis();
    }
    if((millis() - lastPulseTime) >= 1000) {                                    //if the time since the last vss pulse is over 1000 ms
        // TODO: make this calculate depending on the vss pulses per mile value
        speedOut = 0;                                                           // force speed to zero
    }
}


// sets the speed unit of measurement to mph or kph
void setSpeedUnit(bool inputUnit) {
    isMph = inputUnit;
    // tell the display to update to the new unit or something here
}
