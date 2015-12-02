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
uint8_t Module::STR_COUNT = 6;

Module::Module()
	:timer()
	,text(NULL){
	for (uint8_t i=0;i<STR_COUNT;i++)
		text_store[i] = NULL;
}

Module::~Module() {
	for (uint8_t i=0;i<STR_COUNT;i++)
		delete text_store[i];
}

void Module::ui_callback_proxy(UI_t::menucallbackinfo_t& info, char** text, uint8_t select) {
	ptrset(text, select-1); //call weird hackey code thing
	switch(select) {
	case 1:
		ui_callback(info);
		break;
	case 2:
		ui_callback2(info);
		break;
	case 3:
		ui_callback3(info);
		break;
	case 4:
		ui_callback4(info);
		break;
	case 5:
		ui_callback5(info);
		break;
	case 6:
		ui_callback6(info);
		break;
	}
	ui_callback(info);//call callback
}
void Module::alloc(uint8_t len, uint8_t which) {
	text_store[which-1] = new char[len];
}
void Module::regTask() {
	//register as task
	Spin::RegisterTask(this);
}
void Module::ptrset(char **text, uint8_t i) {
	if (!(*text = text_store[i]))
		*text = text_store[i];
	//idea: put this in a callback wrapper method so the module author does not have to call this.
}
