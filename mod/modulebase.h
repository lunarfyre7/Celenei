/*
 * modulebase.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_
#include <iterator>
#include <list>
#include "../config.h"
#include "../ui.h"
#include "Modulereg.h"
extern UI ui;
#define wrapCB(name,obj) void name(UI_t::menucallbackinfo_t& info, char** text) {obj.ui_callback(info, text);}//make callback wrapper
//note: this only uses 4 bytes of ram by itself (not allocating ram for the label string)
class Module_base { //TODO add non ui background callbacks
public:
	Module_base(uint8_t len=0);
	virtual ~Module_base();
	virtual void ui_callback(UI_t::menucallbackinfo_t& info, char** text) {return;}; //ui  callback
	virtual void setup(UI *ui) {ui->PushItem(F("empty"));} //setup ui menu
	virtual void tick() {} //background/non-ui task
//	void setup_all(); //loop though instances and run all setup methods. Use module_reg instead
	MenuItemCallback ext_wrapper;
protected:
	Timer timer;
//	static std::list<Module_base*> instances; //list of instances
	char **text; //pointer for ui dynamic text
	char *text_str; //storage for dynamic text
	void ptrset(char **);//points the text pointer pointer to the string pointer.
};
extern std::list<Module_base*> MODULE_INSTANCES; //list of instances. Wont work as a static member for some reason.
#endif /* MODULEBASE_H_ */
