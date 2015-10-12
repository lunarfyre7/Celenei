#ifndef GUARD_bfw_buffer
#define GUARD_bfw_buffer
#include "config.h"
#include <LiquidCrystal.h>

class Buffer {
public:
	Buffer(uint8_t bufferLen);
	~Buffer();
	void operator()(const char&);
	void operator()(const __FlashStringHelper* Label);
private:
	char *buffer;
};

class LCD_Buffer : public Buffer {
public:
	LCD_Buffer(uint8_t X,  uint8_t Y, uint8_t X2, LiquidCrystal);
	~LCD_Buffer();
private:

};

#endif
