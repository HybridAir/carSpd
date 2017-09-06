// handles all car input and conversion stuff
#include "carInput.hpp"


void carInit() {
    // prepare the VSS input hardware counter thing
    TCCR1A = 0;                                                                 // Configure hardware counter
    TCNT1 = 0;                                                                  // Reset hardware counter to zero

//     for (int thisReading = 0; thisReading < numReadings; thisReading++) {
//         readings2[thisReading] = 0;
//       }
// Serial.print("beep1");

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

    // if it has been samplePeriod since the last computation, or an update is being forced now
    if(millis() - lastSpeedTime >= samplePeriod || updateSpeedNow) {
        TCCR1B = 0;                                                             // stop counting VSS pulses
        uint16_t count = TCNT1;                                                 // Store the hardware VSS pulse counter in a variable
        TCNT1 = 0;                                                              // Reset hardware VSS pulse counter to zero
        uint16_t countOut = count * 10;                                         // multiply the VSS value by 10 to get one "decimal" of accuracy

        updateSpeedNow = false;

        if(firstRun) {
            firstRun = false;
            countOut = 0;                                                       // assume the vehicle is not moving yet, sets the speed value to zero

            // initalize the rolling average to zero
            for (int thisReading = 0; thisReading < numReadings; thisReading++) {
                readings2[thisReading] = 0;
            }
        }

        // stabilize the VSS values using a rolling average
        total = total - readings2[readIndex];                                   // remove the oldest reading from the running total
        readings2[readIndex] = countOut;                                        // add the newest VSS value to the array
        total = total + readings2[readIndex];                                   // add the value we just added to the running total
        readIndex++;                                                            // go to the next array index to prepare for the next update
        if (readIndex >= numReadings) {
            readIndex = 0;                                                      // rollback to the beginning if needed
        }
        average = total / numReadings;                                          // calculate the average


        // the following resets the average if the speed is changing quickly, past a specific threshold
        // this is to help prevent lag caused by the VSS value averaging
        // this codes needs to be after the average calc above or else gcc screams for no discernible reason
        int16_t diff = average - countOut;                                      // calculate the difference between the average and the newest VSS value
        if(abs(diff) > 10) {                                                    // if the absolute difference is greater than the threshold
            // make the average the new VSS value instead of what it was before
            for (uint8_t thisReading = 0; thisReading < numReadings; thisReading++) {
                readings2[thisReading] = countOut;
            }
            average = countOut;
            total = countOut*numReadings;
        }

        uint16_t mph = average/convertMph;                                      // convert the average VSS value to mph, with an extra "decimal" for accuracy (ie 65mph = 650)
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
