#include <LiquidCrystal_I2C.h>

class TextScroller {
	const char *string;
	char *buffer;
	LiquidCrystal_I2C& lcd;
	uint8_t Xa;
	uint8_t Xb;
	uint8_t Y;
	int speed;

	TextScroller(LiquidCrystal_I2C& lcd);
	~TextScroller();
	void StartTask();
	void EndTask();
public:
	TextScroller& DrawArea(uint8_t Xa, uint8_t Y, uint8_t Xb);
	TextScroller& String(const char *string);
	TextScroller& StartScrolling(int speed = 500);
	TextScroller& Beginning();
	TextScroller& Stop();
};