#include "fw_main.h"
#include "spin.h"
#include "timer.h"
#include <pnew.cpp>//library weirdness
// #include <lcdostream>
#include <avr/wdt.h>
#ifndef HEADLESS
#include "ui.h"
#endif
#include "utilfn.h"
#include "modulemanifest.h"



/*
--------------------------------------
###########Built in tasks#############
--------------------------------------
*/
//boot up beep
void TripleBeep() {
	static uint8_t counter;
	static Timer _timer;
	if (_timer.Check(60)) {
		beep();
		if (counter++ == 3) {
			counter = 0;
			Spin::KillTask();
		}
	}
}
//Watchdog reset
void WatchdogReset() {wdt_reset();}

//setup the UI task
// UI ui(LCD_PINS);
#ifndef HEADLESS
	UI ui(LCD_I2C_ADDR);
	void uitask() {ui.Task();};
#endif

/*
--------------------------------------
######################################
--------------------------------------
*/

void setup() {
	wdt_enable(WDTO_2S);
	wdt_reset();
	Serial.begin(115200);
	Serial.println(F("BEAN: start"));
	InitModules();
	pinMode(VALVE_PIN_1, OUTPUT);
	pinMode(VALVE_PIN_2, OUTPUT);
	pinMode(VALVE_PIN_3, OUTPUT);

	Spin::RegisterTask(WatchdogReset);
	Spin::RegisterTask(TripleBeep);

#ifdef HEADLESS
	ui.InitLCD(16, 2);
	Spin::RegisterTask(uitask);
#endif
}

void loop() {
	Spin::LoopTick();
}