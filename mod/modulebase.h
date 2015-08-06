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

class module_base { //TODO add non ui background callbacks
public:
	module_base(uint8_t);
	virtual ~module_base();
	virtual void callback(UI_t::menucallbackinfo_t& info, char** text) {return;};
protected:
	Timer timer;
	char **text;
	char *text_str;
	void ptrset(char **);//points the text pointer pointer to the string pointer.
};

#endif /* MODULEBASE_H_ */
