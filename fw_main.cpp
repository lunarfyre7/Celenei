#include "fw_main.h"
#include "spin.h"
#include "timer.h"
#include <pnew.h>
#include <avr/wdt.h>
#include "ui.h"
#include "mod/modulemanifest.h"
#include <stdio.h>



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
sol::UI ui(LCD_I2C_ADDR);//TODO make this more flexible
void uitask() {ui.Task();};

/*
--------------------------------------
######################################
--------------------------------------
*/

void setup() {
	Serial.begin(115200);
	Serial.println(F("Solaneae: start"));
	ui.InitLCD(LCD_X, LCD_Y);
	Module_reg::run();
//	Module_reg::test();
	Serial.println(F("Registering tasks"));
	Spin::RegisterTask(uitask);
//	Spin::RegisterTask(TripleBeep);

	//start wtd after init is done
//	wdt_enable(WDTO_2S);//enable watchdog timer
//	wdt_reset(); //reset it now
//	Spin::RegisterTask(WatchdogReset); //add reset task
}

void loop() {
	Spin::LoopTick();
}
