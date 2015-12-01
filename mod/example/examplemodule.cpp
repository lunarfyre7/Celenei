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
	:Module()
	,ram(0)
	{
	usingUI(9);
	ui.PushItem(F("ram"), this);
}

Mod_ram::~Mod_ram() {

}
void Mod_ram::ui_callback(mci &info) {
	if(timer.Every(1000))
	{
//		ptrset(text);
		ram = freeMemory();
		sprintf(text_str, ": %db", freeMemory());
		ui.UpdateScreen();
	}
}
//random
Mod_random::Mod_random()
	:Module()
	{
	usingUI(10);
	ui.PushItem(F("rand: "), this);
}
Mod_random::~Mod_random() {}
void Mod_random::ui_callback(mci &info) {
	if(timer.Every(200))
	{
//		ptrset(text);
		sprintf(text_str, ":%lu", random(micros())%999);
		ui.UpdateScreen();
	}
}
//lag
Mod_lag::Mod_lag()
	:Module()
	,ltime(0)
	,lag(0)
	,plag(0)
//	,peak(*this)
	{
	usingUI(9);//setup ui label buffer
	ui.PushItem(F("lag: "), this);//add ui entry to menu
	regTask();//register background task
}

Mod_lag::~Mod_lag() {

}
void Mod_lag::ui_callback(mci &info) {//ui task
	sprintf(text_str, ": %luuS", lag);
}
//Mod_lag::SubMod::SubMod(Mod_lag &p) :Module(), outer(p), timer(){
//	usingUI(9);
//	ui.PushItem(F("P Lag: "), this);
//	regTask();
//}
//void Mod_lag::SubMod::task() {
//	if (timer.Every(500)) {
//		outer.plag = 0;
//	}
//}
//void Mod_lag::SubMod::ui_callback(mci &info) {
//	sprintf(text_str, ": %luuS", outer.plag);
//}
void Mod_lag::task() {//background task
	unsigned long time = micros();
	lag = time - ltime;
	plag = (lag > plag) ? lag : plag;
	ltime = time;
}

//persist
//uint8_t EEMEM eememvar = 0;
//Persist<uint8_t> persist(&eememvar);
PERSIST_D(uint8_t, persist, 0)
Mod_persist::Mod_persist() {

}
void Mod_persist::ui_callback(mci &info) {
//	ptrset(text);
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
	Module* rand = new Mod_random();
	Module* lag = new Mod_lag();
}
