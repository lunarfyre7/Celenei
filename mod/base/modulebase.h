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
//#include "sol/ui.h"
#include "sol/controls.h"
#include "sol/spin.h"
#include "sol/timer.h"
//#include "Modulereg.h"
//extern sol::UI ui;
//using namespace sol;
//#define wrapCB(name,obj) void name(UI_t::menucallbackinfo_t& info, char** text) {obj.ui_callback(info, text);}//make callback wrapper
//#define _makeCB(wrap,class,objname, method) class objname; void wrap(UI_t::menucallbackinfo_t& info, char** text) {objname.method(info, text);}
//#define makeCB(wrap,class,method) _makeCB(wrap, class, UNIQUE_NAME(class##method), method) ///usage makeCB(mycallback, mymodule, mymethod)
namespace sol {
	namespace UI_t {
		struct menucallbackinfo_t {
			bool _new; //menu entry has just been selected
			bool isSelected; //is the current menu item;
			btndir_t button; //the button state
			int  menuindex;
		};
	}
}

class Module;
class UIcallback {
protected:
	char *text_store; //storage for dynamic ui text
	void ptrset(char **);//points the text pointer pointer to the string pointer.
	void alloc(uint8_t len);//call from constructor if using ui callback. len is the length of the ui string
public:
	UIcallback();
	virtual ~UIcallback();
	virtual void callback (sol::UI_t::menucallbackinfo_t& info) =0;//implement your UI callback as this
	virtual void proxy(sol::UI_t::menucallbackinfo_t& info, char** text);//called by the UI system
};
class UIcallbackTimer : public UIcallback {//adds auto refresh timing to the callback
	sol::Timer u_timer;//update timer
	uint16_t period;
public:
	UIcallbackTimer(uint16_t);//pass the refresh time here
	void proxy(sol::UI_t::menucallbackinfo_t& info, char** text);
};

class Module : public Spin::Task { //TODO add non ui background callbacks
public:
	Module();
	virtual ~Module();
	virtual void task() {} //background/non-ui task
protected:
	void regTask();//call from constructor if using task callback
};
#endif /* MODULEBASE_H_ */
