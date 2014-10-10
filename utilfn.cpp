#include "utilfn.h"

void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal lcd) {
	lcd.setCursor(X, Y);
	for (uint8_t i = 0; i < len; ++i)
	{
		lcd.write((uint8_t) 32);
	}
	lcd.setCursor(X, Y);
}