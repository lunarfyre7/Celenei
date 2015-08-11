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
//note: this only uses 4 bytes of ram by itself (not allocating ram for the label string)
class module_base { //TODO add non ui background callbacks
public:
	module_base(uint8_t x=0);
	virtual ~module_base();
	virtual void callback(UI_t::menucallbackinfo_t& info, char** text) {return;}; //ui  callback
	virtual void setup(UI *ui) {ui->PushItem(F("empty"));} //setup ui menu
	virtual void tick() {} //background/non-ui task
protected:
	Timer timer;
	char **text; //pointer for ui dynamic text
	char *text_str; //storage for dynamic text
	void ptrset(char **);//points the text pointer pointer to the string pointer.
};

#endif /* MODULEBASE_H_ */
