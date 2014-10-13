#include "module_test.h"
#include "timer.h"
using namespace UI_t;
extern UI ui;

void Callback1(menucallbackinfo_t info) {
	static Timer timer;
	if (info == NEW) beep();
	else if (info == RIGHT) tone(SPEAKER_PIN, 400, 50);
	else if (info == SELECT) tone(SPEAKER_PIN, 800, 50);
	else if (info == LEFT) tone(SPEAKER_PIN, 1600, 50);
}
void DrawCallback(menucallbackinfo_t info) {
	static Timer timer;
	static int8_t pos = 0;
	static bool up = true;
	if(timer.Check(200))
	{
		ClearSection(0,0,16,ui.lcd);
		ui.lcd.setCursor(pos, 0);
		if (up) {
			if (++pos > 15) {
				--pos;
				up = false;
			}
		}
		else {
			if (--pos < 0) {
				++pos;
				up = true;
			}
		}
		ui.lcd.write(B11111111);
	}
	if (info == SELECT) tone(SPEAKER_PIN, 1000*pos, 20);
}
void ToneGenCallback(menucallbackinfo_t info) {
	static Timer timer;
	static unsigned int freq = 5000;
	switch (info) {
		case RIGHT:
			freq += 500;
			break;
		case LEFT:
			freq -= 500;
			break;
	}
	if (timer.Check(50)) {
		ClearSection(0,0,16,ui.lcd);
		ui.lcd.print(freq);
		tone(SPEAKER_PIN, freq, 50);
	}
}