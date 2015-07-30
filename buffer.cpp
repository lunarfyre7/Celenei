#include "buffer.h"

Buffer::Buffer (uint8_t len) {
	buffer = new char[len];
}
Buffer::~Buffer() {
	delete buffer;
}

LCD_Buffer::LCD_Buffer (uint8_t X, uint8_t Y, uint8_t X2, LiquidCrystal lcd) {
	//insert parent constructor call here
	
}