// handles all car input and conversion stuff
#include "carInput.hpp"


void carInit() {
    // prepare the VSS input hardware counter thing
    TCCR1A = 0;                                                                 // Configure hardware counter
    TCNT1 = 0;                                                                  // Reset hardware counter to zero

    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        readings2[thisReading] = 0;
      }
Serial.print("beep1");

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



// calculates the vehicle speed over the last samplePeriod (usually a second), run this often
// it uses timer 1, which is on arduino uno pin 5, connect it to your car's VSS output
void betterSpeed() {

    //sample the speed for samplePeriod, and only calculate after that samplePeriod has elapsed
    if(millis() - lastSpeedTime >= samplePeriod || updateSpeedNow) {
        TCCR1B = 0;                                                             // stop counting VSS pulses
        uint16_t count = TCNT1;                                                 // Store the hardware VSS pulse counter in a variable
        TCNT1 = 0;                                                              // Reset hardware VSS pulse counter to zero

        if(firstRun) {
            firstRun = false;
            count = 0;
            for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings2[thisReading] = 0;
  }
            Serial.print("beep2");
        }

        Serial.print("raw: ");
        Serial.print(count, DEC);


        // float diff = abs(average - count);
        //
        // if(diff > 2) {
        //     Serial.print("beep3");
        //     for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        // readings2[thisReading] = count;
        // }
        // }


        total = total - readings2[readIndex];
 readings2[readIndex] = (float)count;
 // add the reading to the total:
 total = total + readings2[readIndex];
 // advance to the next position in the array:
 readIndex = readIndex + 1;

 // if we're at the end of the array...
 if (readIndex >= numReadings) {
   // ...wrap around to the beginning:
   readIndex = 0;
 }

 // calculate the average:
 average = total / numReadings;



//uint16_t diff = (uint16_t)average + 3;
//float countout = (float)count;

 // if (count > diff) {
 //     for (int thisReading = 0; thisReading < numReadings; thisReading++) {
 // readings2[thisReading] = countout;
 // }
 //     Serial.print("beep3");
 // }

//  if (count > (average + 3)) {
//          for (int thisReading = 0; thisReading < numReadings; thisReading++) {
//      readings2[thisReading] = count;
//      }
// Serial.print("beep3");
//  }


        Serial.print(" avg: ");
        Serial.println(average);

        updateSpeedNow = false;




        float mph = (average/convertMph)*10;                                      // Convert pulse count into mph.
        //float mph = (count/convertMph)*10;                                      // Convert pulse count into mph.
        //float mph = 650;         // test
        if(!isMph) {
            mph = mph * 1.6093;                                                  // and then convert it to kph if necessary
        }
        uint16_t imph = (uint16_t) mph;                                         // Cast to integer. 10x allows retaining 10th of mph resolution.
        //it converts 659.46516 to 659

        Serial.print("spd: ");
        Serial.println(imph);

        uint16_t x = imph / 10;     //remove the "decimal"
        uint16_t y = imph % 10;     //check the "decimal" to see if the output needs rounding

        // Round to whole mile per hour
        if(y >= 5) {        //if the "decimal" (the 9 in 659) is greater/equal to 5, round up
            roundedMph = x + 1;
        }else{
            roundedMph = x;
        }

        //roundedMph = x;

        //If mph is less than 1mph just show 0mph.
        //Readings of 0.9mph or lower are some what erratic and can
        //occasionally be triggered by electrical noise.
        if(x < 1) {
            roundedMph = 0;
        }

        // check for bad readings
        // if((roundedMph - previousMph) > 60) {
        //     speedOut = previousMph;
        // }else{
        //     speedOut = roundedMph;
        // }

        speedOut = roundedMph;

        //previousMph = roundedMph;                                               // Set previousMph for use in next loop
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
