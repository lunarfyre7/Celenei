/*
 * modulebase.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#include "modulebase.h"
#include "cel/timer.h"
#include "cel/ui.h"
using namespace cel;
extern UI ui;
typedef menucallbackinfo_t mci;
//uint8_t Module::STR_COUNT = 6;

////UIcallback

UIcallback::UIcallback() : text_store(NULL){}
UIcallback::~UIcallback(){
	delete text_store;
}

void UIcallback::proxy(cel::menucallbackinfo_t& info, char** text) {
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

//UIcallbackTimer

UIcallbackTimer::UIcallbackTimer(uint16_t time) : period(time), u_timer() {}

void UIcallbackTimer::proxy(cel::menucallbackinfo_t& info, char** text) {
	//do the thing
	if(u_timer.Every(period)) {
		UIcallback::proxy(info, text);//call base;
		ui.UpdateLine();
	}
}
////Module


Module::Module() {
}

Module::~Module() {
}
