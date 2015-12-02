/*
 * examplemodule.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#ifndef EXAMPLEMODULE_H_
#define EXAMPLEMODULE_H_

#include "../base/modulebase.h"

///module declaration///
using namespace sol;

namespace example_module {

class Mod_ram: public Module {
	int ram;
	class UIcb : public UIcallback {
		Mod_ram &outer;
		Timer timer;
	public:
		UIcb(Mod_ram&);
		void callback(UI_t::menucallbackinfo_t&);
	};
	UIcb callback;
public:
	Mod_ram();
	virtual ~Mod_ram();
//	void ui_callback(UI_t::menucallbackinfo_t&);
};

//class Mod_random: public Module {
//public:
//	Mod_random();
//	virtual ~Mod_random();
//	void ui_callback(UI_t::menucallbackinfo_t&);
//};

class Mod_lag: public Module {
	unsigned long ltime, lag, plag;
	Timer timer;
	class UIcb : public UIcallbackTimer {
		Mod_lag &outer;
	public:
		UIcb(Mod_lag&);
		void callback(UI_t::menucallbackinfo_t&);
	};
	class UIcb2 : public UIcallbackTimer {
		Mod_lag &outer;
	public:
		UIcb2(Mod_lag&);
		void callback(UI_t::menucallbackinfo_t&);
	};
	UIcb cb1;
	UIcb2 cb2;
public:
	Mod_lag();
	virtual ~Mod_lag();
	void task();
};

//class Mod_persist: public Module {
//public:
//	Mod_persist();
//	void ui_callback(UI_t::menucallbackinfo_t&);
//};

void setup();

} // end example_module ns

#endif /* EXAMPLEMODULE_H_ */
