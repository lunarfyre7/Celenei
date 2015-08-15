/*
 * Modulereg.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: Jake
 */

#include "Modulereg.h"
using namespace std;


Module_reg::Module_reg()
	:function(NULL)
{
	DebugP(F("Module reg inited without pointer"));
}
Module_reg::Module_reg(voidfptr_t ptr)
	:function(ptr)
{
	if(ptr)
		reglist.push_back(this);
	DebugP(F("Module reg inited"));
}

Module_reg::~Module_reg() {
	// TODO Auto-generated destructor stub
}
void Module_reg::run() {
	DebugP(F("Module reg run called"));
	for (std::list<Module_reg*>::const_iterator iterator = reglist.begin(), end = reglist.end(); iterator != end; ++iterator) {
		(*iterator)->runf();
		DebugP(F("Module reg registered module called"));
	}
}
void Module_reg::runf() {
	if(function)
		(*function)();
}

list<Module_reg*> Module_reg::reglist;
