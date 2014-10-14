#include "utilfn.h"
#include "config.h"
#include "timer.h"
#include "spin.h"
#include "arduino.h"

void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal lcd) {
	lcd.setCursor(X, Y);
	for (uint8_t i = 0; i < len; ++i)
	{
		lcd.write((uint8_t) 32);
	}
	lcd.setCursor(X, Y);
}

// void beep() {
// 	//simple beep
// 	tone (SPEAKER_PIN, 1000, 20);
// }

void beep() {//todo: Add recursion
	// const uint8_t tone1len = 30;
	// const uint8_t tone2len = 20;
	const uint8_t tone1len = 30;
	const uint8_t tone2len = 20;
	const int tone1 = 500;
	const int tone2 = 1200;
	static bool inloop;
	static Timer timer;
	if (inloop) { //loop
		if (timer.StaticCheck(tone1len)) {//delay 1. run tone till time form Tone1len has passed
			if (timer.StaticCheck(tone1len + tone2len)) { //delay 2. run till time tone2len has passed after tone1.
				//kill the task
				noTone(SPEAKER_PIN);
				inloop = false;
				Spin::KillTask();
				return;
			}
			tone(SPEAKER_PIN, tone2);//note how this is the reverse order of a normal delay()
			return;
		}
		tone(SPEAKER_PIN, tone1);

	} else {//start the loop
		inloop = true;
		timer.Reset();
		Spin::RegisterTask(beep);
		return;
	}
}