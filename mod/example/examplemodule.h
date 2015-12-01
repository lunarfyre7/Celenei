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
public:
	Mod_ram();
	virtual ~Mod_ram();
	void ui_callback(UI_t::menucallbackinfo_t&);
private:
	int ram;
};

class Mod_random: public Module {
public:
	Mod_random();
	virtual ~Mod_random();
	void ui_callback(UI_t::menucallbackinfo_t&);
};

class Mod_lag: public Module {
private:
//	class SubMod : public Module {//submodule for another line
//	public:
//		SubMod(Mod_lag &);
//		Mod_lag &outer;
//		void ui_callback(UI_t::menucallbackinfo_t&);
//		void task();
//		Timer timer;
//	};
	unsigned long ltime, lag, plag;
public:
	Mod_lag();
	virtual ~Mod_lag();
	void ui_callback(UI_t::menucallbackinfo_t&);
	void task();
//	SubMod peak;
};

class Mod_persist: public Module {
public:
	Mod_persist();
	void ui_callback(UI_t::menucallbackinfo_t&);
};

void setup();

} // end example_module ns

#endif /* EXAMPLEMODULE_H_ */
