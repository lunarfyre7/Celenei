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
#include "config.h"
//#include "cel/ui.h"
#include "cel/controls.h"
#include "cel/spin.h"
#include "cel/timer.h"
#include "cel/uitypes.h"
//#include "Modulereg.h"
//extern sol::UI ui;
//using namespace sol;
//#define wrapCB(name,obj) void name(UI_t::menucallbackinfo_t& info, char** text) {obj.ui_callback(info, text);}//make callback wrapper
//#define _makeCB(wrap,class,objname, method) class objname; void wrap(UI_t::menucallbackinfo_t& info, char** text) {objname.method(info, text);}
//#define makeCB(wrap,class,method) _makeCB(wrap, class, UNIQUE_NAME(class##method), method) ///usage makeCB(mycallback, mymodule, mymethod)

class Module;
class UIcallback {
protected:
	char *text_store; //storage for dynamic ui text
	void ptrset(char **);//points the text pointer pointer to the string pointer.
	void alloc(uint8_t len);//call from constructor if using ui callback. len is the length of the ui string
public:
	UIcallback();
	virtual ~UIcallback();
	virtual void callback (cel::menucallbackinfo_t& info) =0;//implement your UI callback as this
	virtual void proxy(cel::menucallbackinfo_t& info, char** text);//called by the UI system
};
class UIcallbackTimer : public UIcallback {//adds auto refresh timing to the callback
	cel::Timer u_timer;//update timer
	uint16_t period;
public:
	UIcallbackTimer(uint16_t);//pass the refresh time here
	void proxy(cel::menucallbackinfo_t& info, char** text);
};

class Module { //TODO add non ui background callbacks
public:
	Module();
	virtual ~Module();
	virtual void task() {} //background/non-ui task
};
#endif /* MODULEBASE_H_ */
