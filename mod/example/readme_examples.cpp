/*
 * readme_examples.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: Jake Vandereay
 */

#include "readme_examples.h"

namespace example_module_1 {

	MyModule::MyModule() :UIcallbackTimer(1000) /*pass the refresh rate to the UI callback mixin*/ {
		ui.PushItem(F("MyModule"));//push a line with text into the menu
		ui.PushItem(F("says "), this);//push a line with a static label and a dynamic label written by the callback.
		alloc(10);//allocate a 10 char string for the UI callback
	}
	void MyModule::task() {
		//this will be called over and over in a loop
		//do NOT use delay(), use Timer instead!!!
	}
	void MyModule::callback(sol::menucallbackinfo_t &) {//UIcallback
		text_store = "hello";//set the dynamic label text
		ui.UpdateLine(); //tell the ui to update the line
	}
	void setup() {
		//this is the setup function for the whole module.
		//It creates an instance of the module class and runs other setup code. All we do in this example is create an instance of the module class though.
		MyModule *mod = new MyModule();//create an instance of the module that won't go away after this function exits.
	}

}//example_module_1 end
