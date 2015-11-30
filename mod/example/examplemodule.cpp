/*
 * examplemodule.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */
#include "examplemodule.h"
#include "sol/timer.h"
#include <MemoryFree.h>
#include "Arduino.h"
#include "sol/persist.h"

using namespace UI_t;
using namespace example_module;

typedef menucallbackinfo_t mci;
Mod_ram::Mod_ram()
	:Module(9)
	,ram(0)
	{
}

Mod_ram::~Mod_ram() {

}
void Mod_ram::ui_callback(mci &info, char** text) {
	if(timer.Every(1000))
	{
		ptrset(text);
		ram = freeMemory();
		sprintf(text_str, ": %db", freeMemory());
		ui.UpdateScreen();
	}
}

void Mod_ram::setup() {
	ui.PushItem(F("ram"), this);
}
//random
Mod_random::Mod_random()
	:Module(10)
	{}
//Mod_random::Mod_random
void Mod_random::setup() {
	return;
}
void Mod_random::ui_callback(mci &info, char** text) {
	if(timer.Every(200))
	{
		ptrset(text);
		sprintf(text_str, ":%lu", random(micros())%999);
		ui.UpdateScreen();
	}
}
//lag
Mod_lag::Mod_lag()
	:Module(5)//4 char + end sentinel
	,ltime(0)
	,loopcount(false)
	{
}

Mod_lag::~Mod_lag() {

}
void Mod_lag::ui_callback(mci &info, char** text) {
	if(timer.StaticCheck(101))
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

//persist
//uint8_t EEMEM eememvar = 0;
//Persist<uint8_t> persist(&eememvar);
PERSIST_D(uint8_t, persist, 0)
Mod_persist::Mod_persist() {

}
void Mod_persist::ui_callback(mci &info, char** text) {
	ptrset(text);
	if(timer.Every(100)) {
		//read value from eeprom
//		buffer = eeprom_read_byte(&persistantint);
		if(info.button == right) {
//			eeprom_write_byte(&persistantint, --buffer);
//			persist.set(persist.get() - 1);
			persist = persist.get() -1;
			tone(SPEAKER_PIN, 1000, 30);
		}
		if(info.button == left) {
//			eeprom_write_byte(&persistantint, ++buffer);
//			persist.set(persist.get() + 1);
			persist = persist.get() +1;
			tone(SPEAKER_PIN, 1000, 30);
		}
		sprintf(text_str, "%d", persist.get());
	}
}

//setup code for the whole module
void example_module::setup() {
	ui.PushItem(F("Solaneae"));
	//ui.PushMenu('example');
//	ui.PushItem(F("example module")).LinkTo('example');
	//add something like ui.setcontext('menuname') here
	Module* ram = new Mod_ram();
	ram->setup();
}
