/*
 * examplemodule.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#include "examplemodule.h"
#include "../timer.h"
#include <MemoryFree.h>
#include "Arduino.h"
using namespace UI_t;
extern UI ui;
typedef menucallbackinfo_t mci;
mod_ram::mod_ram()
	:module_base(9)
	,ram(0)
	{
}

mod_ram::~mod_ram() {

}
void mod_ram::callback(mci &info, char** text) {
	if(timer.Every(1000))
	{
		ptrset(text);
		ram = freeMemory();
		sprintf(text_str, ": %db", freeMemory());
		ui.UpdateScreen();
	}
}

//random
mod_random::mod_random()
	:module_base(10)
	{
}

mod_random::~mod_random() {

}
void mod_random::callback(mci &info, char** text) {
	if(timer.Every(200))
	{
		ptrset(text);
		sprintf(text_str, ":%lu", random(micros()));
		ui.UpdateScreen();
	}
}
//lag
mod_lag::mod_lag()
	:module_base(10)
	,ltime(0)
	,loopcount(false)
	{
}

mod_lag::~mod_lag() {

}
void mod_lag::callback(mci &info, char** text) {
	if(timer.StaticCheck(200))
	{
		ptrset(text);
		loopcount = !loopcount;
		switch(loopcount){//faster than if else
		case false:
			ltime = millis();
			break;
		case true:
			sprintf(text_str, ": %lu", millis() - ltime);
			ui.UpdateScreen();
			timer.Reset();
			break;
		}
	}
}
