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
//uint8_t Module::STR_COUNT = 6;

////UIcallback

UIcallback::UIcallback() : text_store(NULL){}
UIcallback::~UIcallback(){
	delete text_store;
}

void UIcallback::proxy(sol::UI_t::menucallbackinfo_t& info, char** text) {
	ptrset(text);
	callback(info);
}
void UIcallback::ptrset(char **text) {
	if (!(*text = text_store))
		*text = text_store;
}

void UIcallback::alloc(uint8_t len) {
	text_store = new char[len];
}

////Module


Module::Module() {
}

Module::~Module() {
}

void Module::regTask() {
	//register as task
	Spin::RegisterTask(this);
}
