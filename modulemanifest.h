/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#################################################
//include modules here
#include "module_test.h"
//#################################################

void InitModules() {
	using namespace UI_t;
	extern UI ui;
	//#############################################
	//This is where the main menu is defined.
	//Add your modules and menu items to the menu here.
	ui.PushItem(F("Callback draw"), DrawCallback);
	ui.PushItem(F("tone gen"), ToneGenCallback);
	ui.PushItem(F("A label"), F("Beep on select"), Callback1);
	ui.PushItem(F("Another label"), F("This does nothing"));
	//#############################################
}