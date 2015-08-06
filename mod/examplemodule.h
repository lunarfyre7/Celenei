/*
 * examplemodule.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#ifndef EXAMPLEMODULE_H_
#define EXAMPLEMODULE_H_

#include "modulebase.h"

class mod_ram: public module_base {
public:
	mod_ram();
	virtual ~mod_ram();
	void callback(UI_t::menucallbackinfo_t&, char**);
private:
	int ram;
};

class mod_random: public module_base {
public:
	mod_random();
	virtual ~mod_random();
	void callback(UI_t::menucallbackinfo_t&, char**);
};

#endif /* EXAMPLEMODULE_H_ */
