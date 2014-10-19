#include "fw_main.h"
#include "spin.h"
#include "timer.h"
#include <pnew.cpp>//library weirdness
// #include <lcdostream>
#include <avr/wdt.h>
#include "ui.h"
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
UI ui(LCD_PINS);
void uitask() {ui.Task();};

/*
--------------------------------------
######################################
--------------------------------------
*/

void setup() {
	wdt_enable(WDTO_2S);
	wdt_reset();
	Serial.begin(9600);
	Serial.println(F("BEAN: start"));
	ui.InitLCD(16, 2);
	InitModules();
	pinMode(VALVE_PIN_1, OUTPUT);
	pinMode(VALVE_PIN_2, OUTPUT);
	pinMode(VALVE_PIN_3, OUTPUT);

	Spin::RegisterTask(WatchdogReset);
	Spin::RegisterTask(uitask);
	Spin::RegisterTask(TripleBeep);
}

void loop() {
	Spin::LoopTick();
}