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
using namespace BEAN;

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
	if (_timer.Check(60)) {
		beep();
		if (counter++ == 3) {
			Spin::KillTask();
		}
	}
	// beep();
	// Spin::KillTask();
}
UI ui(16, 2);
void uitask() {ui.Task();};
void callback1(menucallbackinfo_t info) {
	static Timer timer;
	if (info == NEW) beep();
	else if (info == RIGHT) tone(8, 400, 50);
	else if (info == SELECT) tone(8, 800, 50);
	else if (info == LEFT) tone(8, 1600, 50);
}
void drawcallback(menucallbackinfo_t info) {
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
	if (info == SELECT) tone(8, 1000*pos, 20);
}
void toneGenCallback(menucallbackinfo_t info) {
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
		tone(8, freq, 50);
	}
}
void lcdTest () {
	//LiquidCrystal lcd(11,10,5,4,3,2);
	//lcd.begin(16,2);
	
	//MOVE THESE TO THEIR OWN MODULE
	ui.PushItem(F("BEAN FW UI Test"), drawcallback);
	ui.PushItem(F("tone gen"), toneGenCallback);
	ui.PushItem(F("A label"), F("Beep on select"), callback1);
	ui.PushItem(F("Another label"), F("This does nothing"));

	//Better
	InitModules();

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
