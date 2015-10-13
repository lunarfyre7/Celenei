/*
 * modulebase.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#include "modulebase.h"
#include "sol/timer.h"
using namespace UI_t;
extern UI ui;
typedef menucallbackinfo_t mci;
std::list<Module_base*> MODULE_INSTANCES;

Module_base::Module_base(uint8_t len)
	:timer()
	,text(NULL)
	,text_str(new char[len]){
	MODULE_INSTANCES.push_back(this);
}

Module_base::~Module_base() {
	delete text_str;
	MODULE_INSTANCES.remove(this);
}
void Module_base::ptrset(char **text) {
	if (!(*text = text_str))
		*text = text_str;
	//idea: put this in a callback wrapper method so the module author does not have to call this.
}
//void Module_base::setup_all () {
//	for (std::list<Module_base*>::iterator it=MODULE_INSTANCES.begin(); it!=MODULE_INSTANCES.end(); ++it) {
//		if((*it)->ext_wrapper)
//			(*it)->setup(&ui);
//		else
//			Serial.println(F("[error] undefined wrapper pointer"));
//	}
//}
