

#include "disp/big.hpp"


//************************************************************************
void	BigNumber_SendCustomChars(void)
{
uint8_t	customCharDef[10];
uint8_t	ii;
int		jj;

	for (ii=0; ii<8; ii++)
	{
		for (jj=0; jj<8; jj++)
		{
			customCharDef[jj]	=	pgm_read_byte_near(gBigFontShapeTable + (ii * 8) + jj);
		}
		lcd.createChar(ii, customCharDef);
	}
}

//************************************************************************
//*	returns the width of the character
int	DrawBigChar(int xLocation, int yLocation, char theChar) {
	int		ii;
	char	theByte;
	int		specialIndex;
	int charWidth =	3;
	int offset = 6 * (theChar - 0x30);

	lcd.setCursor(xLocation, yLocation);
	for (ii=0; ii<3; ii++)
	{
		theByte	=	pgm_read_byte_near(gBigFontAsciiTable + offset + ii);
		lcd.write(theByte);
	}

	lcd.setCursor(xLocation, yLocation + 1);
	offset	+=	3;
	for (ii=0; ii<3; ii++)
	{
		theByte	=	pgm_read_byte_near(gBigFontAsciiTable + offset + ii);
		lcd.write(theByte);
	}

	return(charWidth + 1);
}
