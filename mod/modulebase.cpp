/*
 * modulebase.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#include "modulebase.h"
#include "../timer.h"
using namespace UI_t;
extern UI ui;
typedef menucallbackinfo_t mci;

module_base::module_base(uint8_t len)
	:timer()
	,text(NULL)
	,text_str(new char[len]){

}

module_base::~module_base() {
	delete text_str;
}
void module_base::ptrset(char **text) {
	if (!(*text = text_str))
		*text = text_str;
	//idea: put this in a callback wrapper method so the module author does not have to call this.
}
