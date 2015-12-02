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
	,callback(*this)
	{
	ui.PushItem(F("ram"), &callback);
}

Mod_ram::~Mod_ram() {

}

Mod_ram::UIcb::UIcb(Mod_ram& mod): UIcallback(), timer(), outer(mod) {
	alloc(9);//allocate a 9 char string for writing to
}
void Mod_ram::UIcb::callback(mci &info) {
	if(timer.Every(1000))//this callback handles it's own timing
	{
		outer.ram = freeMemory();
		sprintf(text_store, ": %db", freeMemory());
		ui.UpdateLine();
	}
}
////random
//Mod_random::Mod_random()
//	:Module()
//	{
//	alloc(10);
//	ui.PushItem(F("rand: "), this);
//}
//Mod_random::~Mod_random() {}
//void Mod_random::ui_callback(mci &info) {
//	if(timer.Every(200))
//	{
////		ptrset(text);
//		sprintf(text_store[0], ":%lu", random(micros())%999);
//		ui.UpdateScreen();
//	}
//}
//lag
Mod_lag::Mod_lag()
	:Module()
	,ltime(0)
	,lag(0)
	,plag(0)
	,timer()
	,cb1(*this)
	,cb2(*this)
	{
	ui.PushItem(F("lag: "), &cb1);//add ui entry to menu
	ui.PushItem(F("P.lag: "), &cb2);//add 2nd callback to menu
	regTask();//register background task
}

Mod_lag::~Mod_lag() {

}
//void Mod_lag::ui_callback(mci &info) {//ui task
//	sprintf(text_store[0], ": %luuS", lag);
//}
//void Mod_lag::ui_callback2(mci &info) {//ui task
//	sprintf(text_store[1], ": %luuS", plag);
//}
Mod_lag::UIcb::UIcb(Mod_lag& m) : outer(m), UIcallbackTimer(100) {//this callback using built in timing
	alloc(9);
}
Mod_lag::UIcb2::UIcb2(Mod_lag& m) : outer(m), UIcallbackTimer(100) {
	alloc(9);
}
void Mod_lag::UIcb::callback(mci &info) {
	sprintf(text_store, "%luuS", outer.lag);
}
void Mod_lag::UIcb2::callback(mci &info) {
	sprintf(text_store, "%luuS", outer.plag);
}
void Mod_lag::task() {//background task
	unsigned long time = micros();
	lag = time - ltime;
	plag = (lag > plag) ? lag : plag;
	ltime = time;
	if (timer.Every(100))
		plag = 0;
}

////persist
////uint8_t EEMEM eememvar = 0;
////Persist<uint8_t> persist(&eememvar);
//PERSIST_D(uint8_t, persist, 0)
//Mod_persist::Mod_persist() {
//
//}
//void Mod_persist::ui_callback(mci &info) {
////	ptrset(text);
//	if(timer.Every(100)) {
//		//read value from eeprom
////		buffer = eeprom_read_byte(&persistantint);
//		if(info.button == right) {
////			eeprom_write_byte(&persistantint, --buffer);
////			persist.set(persist.get() - 1);
//			persist = persist.get() -1;
//			tone(SPEAKER_PIN, 1000, 30);
//		}
//		if(info.button == left) {
////			eeprom_write_byte(&persistantint, ++buffer);
////			persist.set(persist.get() + 1);
//			persist = persist.get() +1;
//			tone(SPEAKER_PIN, 1000, 30);
//		}
//		sprintf(text_store[0], "%d", persist.get());
//	}
//}

//setup code for the whole module
void example_module::setup() {
	ui.PushItem(F("Solaneae"));
	//ui.PushMenu('example');
//	ui.PushItem(F("example module")).LinkTo('example');
	//add something like ui.setcontext('menuname') here
	Module* ram = new Mod_ram();
//	Module* rand = new Mod_random();
	Module* lag = new Mod_lag();
	////menu example/test////
	ui.PushMenu('meow');//add a menu called meow
	ui.PushItem(F("link to submenu")).LinkTo('meow');
	ui.PushItem(F("This is a")).SetParent('meow');
	ui.PushItem(F("submenu")).SetParent('meow');
	ui.PushItem(F("Meow =^..^=")).SetParent('meow');
	ui.PushItem(F("Return to root")).LinkTo('root').SetParent('meow');
}
