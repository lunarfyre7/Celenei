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



#endif /* EXAMPLEMODULE_H_ */
