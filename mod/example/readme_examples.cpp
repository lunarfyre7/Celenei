/*
 * readme_examples.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: Jake Vandereay
 */

#include "readme_examples.h"

namespace example_module_1 {

	MyModule::MyModule() {
		ui.PushItem(F("MyModule"));//push a line with text into the menu
		ui.PushItem(F("says: "), this);//push a line with a static label and a dynamic label written by the callback.
	}
	void MyModule::task() {
		//this will be called over and over in a loop
		//do NOT use delay(), use Timer instead!!!
	}

}//example_module_1 end
