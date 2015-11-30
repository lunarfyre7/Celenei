/*
 * modulebase.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#include "modulebase.h"
#include "sol/timer.h"
using namespace sol;
using namespace UI_t;
//extern UI ui;
typedef menucallbackinfo_t mci;

Module::Module()
	:timer()
	,text(NULL)
	,text_str(NULL){
}

Module::~Module() {
	delete text_str;
}

void Module::ui_callback_proxy(UI_t::menucallbackinfo_t& info, char** text) {
	ptrset(text); //call weird hackey code thing
	ui_callback(info, text);//call callback
}
void Module::usingUI(uint8_t len) {
	text_str = new char[len];
}
void Module::regTask() {
	//register as task
	Spin::RegisterTask(this);
}
void Module::ptrset(char **text) {
	if (!(*text = text_str))
		*text = text_str;
	//idea: put this in a callback wrapper method so the module author does not have to call this.
}
