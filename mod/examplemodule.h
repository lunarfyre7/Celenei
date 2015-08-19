/*
 * examplemodule.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#ifndef EXAMPLEMODULE_H_
#define EXAMPLEMODULE_H_

#include "modulebase.h"
#include "Modulereg.h"

///module def///

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


///setup and wrapper code///
#ifndef IS_MOD_DEF
//Mod_ram ram;
//wrapCB(ramCB, ram);
makeCB(ramCB, Mod_ram, ui_callback);
static void ramwrap() {
	ui.PushItem(F("ram"), ramCB);
	DebugP(F("ramwrap"));
}
//void randwrap() {
//
//}
//void lagwrap() {
//
//}
Module_reg ramptr(ramwrap);
#endif //MOD_WRAPPER

#endif /* EXAMPLEMODULE_H_ */
