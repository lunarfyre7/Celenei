/*
 * examplemodule.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#ifndef EXAMPLEMODULE_H_
#define EXAMPLEMODULE_H_

#include "../base/modulebase.h"
#include "../base/Modulereg.h"

///module declaration///
using namespace sol;

class Mod_ram: public Module_base {
public:
	Mod_ram();
	virtual ~Mod_ram();
	void ui_callback(UI_t::menucallbackinfo_t&, char**);
private:
	int ram;
};

class Mod_random: public Module_base {
public:
	Mod_random();
//	virtual ~Mod_random();
	void setup(UI*);
	void ui_callback(UI_t::menucallbackinfo_t&, char**);
};

class Mod_lag: public Module_base {
public:
	Mod_lag();
	virtual ~Mod_lag();
	void ui_callback(UI_t::menucallbackinfo_t&, char**);
private:
	unsigned long ltime;
	bool loopcount;
};

class Mod_persist: public Module_base {
public:
	Mod_persist();
	void ui_callback(UI_t::menucallbackinfo_t&, char**);
};


///setup and wrapper code///
#ifdef IS_MOD_MANIFEST
//Mod_ram ram;
//wrapCB(ramCB, ram);
makeCB(ramCB, Mod_ram, ui_callback);//make a ui callback
makeCB(randCB, Mod_random, ui_callback);
makeCB(lagCB, Mod_lag, ui_callback);
makeCB(persistCB, Mod_persist, ui_callback);
static void wrap() {
	PLF("example module wrap called");
	ui.PushItem(F("Solaneae demo"));
	ui.PushItem(F("ram"), ramCB); //push callbacks into the ui system
	ui.PushItem(F("rand"), randCB);
	ui.PushItem(F("lag"), lagCB);
	ui.PushItem(F("persist"), persistCB);
}
Module_reg examplereg(wrap);
//Module_reg *examplereg = new Module_reg(wrap);
#endif //IS_MOD_MANIFEST

#endif /* EXAMPLEMODULE_H_ */
