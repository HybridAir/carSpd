// handles big number formatting and display
#include "disp/big.hpp"


// writes all the custom big number chars to the display's cgram
void writeBigNumChars() {
    uint8_t customCharDef[10];

    // for each required custom character (all 8 of them)
    for (uint8_t i=0; i<8; i++) {
        for (uint8_t x=0; x<8; x++) {
            customCharDef[x]   =   pgm_read_byte_near(gBigFontShapeTable + (i * 8) + x);
        }
        lcd.createChar(i, customCharDef);                                       // write the extracted character to cgram
    }
}


// draws a big number at the specified location, needs the x position and the number character to draw
// returns the display width used
uint8_t drawBigNum(int8_t x, uint8_t theChar) {
    uint8_t charWidth = 3;
    uint8_t offset = 6 * (theChar - 0x30);

    uint8_t xOffset = 0;

    if(x < 0) {
        x = 0;
        xOffset = 1;
    }
    lcd.setCursor(x, 0);
    for (uint8_t i=0+xOffset; i<3; i++) {
        lcd.write(pgm_read_byte_near(gBigFontAsciiTable + offset + i));
    }

    lcd.setCursor(x, 1);
    offset  +=  3;
    for (uint8_t i=0+xOffset; i<3; i++) {
        lcd.write(pgm_read_byte_near(gBigFontAsciiTable + offset + i));
    }

    return charWidth + 1 ;
}


// draws a big number starting at the specified offset, at the specified place
// meant for displaying multiple numbers

void clearBigNum(uint8_t x) {
    lcd.setCursor(x, 0);
    lcd.print("   ");
    lcd.setCursor(x, 1);
    lcd.print("   ");
}
