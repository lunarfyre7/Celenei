#include "fw_main.h"
#include "cel/spin.h"
#include "cel/timer.h"
#include <pnew.h>
#include <avr/wdt.h>
#include "cel/ui.h"
#include "../../mod/modulemanifest.h"
#include "../../mod/base/modulebase.h"
#include <stdio.h>



/*
--------------------------------------
###########Built in tasks#############
--------------------------------------
*/
//boot up beep
//void TripleBeep() {
//	static uint8_t counter;
//	static Timer _timer;
//	if (_timer.Check(60) {
//		beep();
//		if (counter++ == 3) {
//			counter = 0;
//			Spin::KillTask();
//		}
//	}
//}

//Spin test
class TaskTest : public Spin::Task {
	void task() {
		PLF("test task created");
		Spin::KillTask();
		PLF("test task killed");
	}
};

//Watchdog reset
class WatchdogReset : public Spin::Task {
	void task() {
		wdt_reset();
	}
};

//setup the UI task
// UI ui(LCD_PINS);
cel::UI ui(LCD_I2C_ADDR);

/*
--------------------------------------
######################################
--------------------------------------
*/

void setup() {
#ifdef DIRECT_5WAY_BUTTONS //if using buttons
	pinMode(BUTTON_PIN_U, INPUT_PULLUP);
	pinMode(BUTTON_PIN_D, INPUT_PULLUP);
	pinMode(BUTTON_PIN_L, INPUT_PULLUP);
	pinMode(BUTTON_PIN_R, INPUT_PULLUP);
	pinMode(BUTTON_PIN_C, INPUT_PULLUP);
#endif

	Serial.begin(115200);
	Serial.println(F("Solaneae: start"));
	ui.InitLCD(LCD_X, LCD_Y);
//	Module_reg::run();
	module_setup();
	Spin::Task *uitask, *tasktest, *WDRtask;
	uitask = &ui;//pointer to ui instance
	tasktest = new TaskTest;
	WDRtask = new WatchdogReset;

	Spin::RegisterTask(uitask);
	Spin::RegisterTask(tasktest);

	//start wtd
	wdt_enable(WDTO_2S);//enable watchdog timer
	wdt_reset(); //reset it now
	Spin::RegisterTask(WDRtask); //add reset task
}

void loop() {
	Spin::LoopTick();
}
