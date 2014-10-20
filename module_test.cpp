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
		tone(SPEAKER_PIN, freq);
	}
}

uint8_t valveEN = 0b00000001;
uint8_t numOfValves;
void SequenceTest(menucallbackinfo_t info) {
	static Timer t;

	switch(info) {
		case RIGHT:
			valveEN = 0b11;
		break;
		case LEFT:
			valveEN = 0b1;
		break;
	}
	// if (t.First() || t.Check(100)) {
	// 	ClearSection(0,0,16,ui.lcd);
	// 	for (uint8_t i=0; i!=numOfValves; ++i) {
	// 		ui.lcd.print(valveEN >> i & 0b1);
	// 	}
	// }
}
void SequenceTestTask() {
	const uint8_t valvePins[] = {
			VALVE_PIN_1,
			VALVE_PIN_2,
			VALVE_PIN_3
		};
	// static uint8_t valveEN = 0b00000001;
	numOfValves = sizeof(valvePins) / sizeof(valvePins[0]);

	//const uint32_t Interval = 15 * 60 * 1000;
	const int Interval =  1000;

	static Timer timer;

	if (timer.First() || timer.Check(Interval)) {
		//////Byte check (number >> position) & 1
		//beep();
		// if ((valveEN >> numOfValves) & 1) { //reset position if past limit
		// 	valveEN = 1;
		// }
		for (uint8_t i=0; i!=numOfValves; ++i) {
			digitalWrite(valvePins[i],valveEN >> i & 0b1);
		}
		//valveEN = valveEN << 1; //shift position
		valveEN = (valveEN << 1) | (valveEN >> numOfValves - 1);
	}
}