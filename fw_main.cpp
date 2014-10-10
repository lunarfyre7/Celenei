#include "fw_main.h"
#include "spin.h"
#include "timer.h"
#include <pnew.cpp>//library weirdness
// #include <lcdostream>
#include "ui.h"



/*
--------------------------------------
###########Test Functions#############
--------------------------------------
*/
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
void beepTest() {
	static uint8_t counter;
	static Timer _timer;
	if (_timer.Check(100)) {
		beep();
		if (counter++ == 5) {
			Spin::KillTask();
		}
	}
	// beep();
	// Spin::KillTask();
}
UI ui(16, 2);
void uitask() {ui.Task();};

void lcdTest () {
	//LiquidCrystal lcd(11,10,5,4,3,2);
	//lcd.begin(16,2);
	

	ui.PushItem("A label", "some info");
	ui.PushItem("Another label", "some other info");

	Spin::RegisterTask(uitask);
}

// void screenTest(const uint8_t& taskIndex) {
// 	//const char message = "hello world";
// 	static bool init = true;

// 	if (init) {
// 		LiquidCrystal lcd(11,10,5,4,3,2);
// 		lcd.begin(16,2);
// 		std::olcdstream stream(lcd);
// 		stream << std::clear() << "testing";

// 		init = false;
// 	}
// }

/*
--------------------------------------
#######End Test Functions#############
--------------------------------------
*/

void setup() {
	Serial.begin(9600);
	Serial.println(F("BEAN: start"));
	lcdTest();
	//menuTest();
	//beep();
	// Spin::RegisterTask(blinkTask);
	Spin::RegisterTask(beepTest);
	//Spin::RegisterTask(screenTest);
}

void loop() {
	Spin::LoopTick();
}

// int main()
// {
// 	setup();
// 	while (1) {
// 		loop();
// 	}
// 	return 0;
// }
