/*
 * examplemodule.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#include "examplemodule.h"
#include "../timer.h"
#include <MemoryFree.h>
using namespace UI_t;
extern UI ui;
typedef menucallbackinfo_t mci;
example_module::example_module()
	:ram(0)
	,timer()
	,text(NULL)
	,text_str(new char[9])
	{
}

example_module::~example_module() {
	delete text_str;
}
void example_module::callback(mci &info, char** text) {
	if(timer.Every(1000))
	{
		DebugP("callback");
		ram = freeMemory();
		if (!(*text = text_str))
			*text = text_str;
		sprintf(text_str, ": %db", freeMemory());
		ui.UpdateScreen();
	}
}
