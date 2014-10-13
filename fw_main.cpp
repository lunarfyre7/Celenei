#include "fw_main.h"
#include "spin.h"
#include "timer.h"
#include <pnew.cpp>//library weirdness
// #include <lcdostream>
#include "ui.h"
#include "utilfn.h"
#include "modulemanifest.h"



/*
--------------------------------------
###########Test Functions#############
--------------------------------------
*/
// using namespace UI_t;


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
UI ui(11,10,5,4,3,2);
void uitask() {ui.Task();};

/*
--------------------------------------
#######End Test Functions#############
--------------------------------------
*/

void setup() {
	Serial.begin(9600);
	Serial.println(F("BEAN: start"));
	ui.InitLCD(16, 2);
	InitModules();

	Spin::RegisterTask(uitask);
	Spin::RegisterTask(TripleBeep);
}

void loop() {
	Spin::LoopTick();
}