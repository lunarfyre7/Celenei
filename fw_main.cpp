#include "fw_main.h"
#include "spin.h"
#include "timer.h"
//#include <pnew.cpp>
#include <avr/wdt.h>
#include "ui.h"
#include "modulemanifest.h"
#include <stdio.h>

//fix for pnew.cpp build fail
void* operator new(size_t size_,void *ptr_)
{
	return ptr_;
}




/*
--------------------------------------
###########Built in tasks#############
--------------------------------------
*/
//boot up beep
void TripleBeep() {
	static uint8_t counter;
	static Timer _timer;
	DebugP(F("triple beep"));
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
UI ui(LCD_I2C_ADDR);
void uitask() {ui.Task();};

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
	ui.InitLCD(LCD_X, LCD_Y);
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
