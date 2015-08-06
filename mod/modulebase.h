/*
 * modulebase.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_
#include "../config.h"
#include "../ui.h"

class module_base {
public:
	module_base();
	virtual ~module_base();
	virtual void callback(UI_t::menucallbackinfo_t& info, char** text) {return;};
};

#endif /* MODULEBASE_H_ */
