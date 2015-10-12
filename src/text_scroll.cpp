#include "arduino.h"
#include "text_scroll.h"
#include "timer.h"
#include "spin.h"

TextScroller::TextScroller (LiquidCrystal_I2C& lcd)
	:lcd(lcd)
	,Xa(0)
	,Xb(0)
	,Y(0)
	,speed(0)
	,string(NULL)
	,buffer(NULL)
{
	//buffer = new char[];
}
TextScroller::~TextScroller () {
	delete buffer;
}

void TextScroller::StartTask() {

}
void TextScroller::EndTask() {

}
TextScroller& TextScroller::DrawArea(uint8_t Xa, uint8_t Y, uint8_t Xb) {
	return *this;
}
TextScroller& TextScroller::String(const char *str) {
	string = str;
	return *this;
}
TextScroller& TextScroller::StartScrolling(int speed /*=500*/) {
	return *this;
}
TextScroller& TextScroller::Beginning() {
	return *this;
}
TextScroller& TextScroller::Stop() {
	return *this;
}