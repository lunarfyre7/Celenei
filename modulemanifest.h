#include "config.h"
#include "ui.h"//redundant
#include "spin.h"
/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#################################################
//include modules here

#ifdef EN_TEST_MODULE
#include "module_test.h"
#endif

//#################################################

void InitModules() {
	using namespace UI_t;
	extern UI ui;
	//#############################################
	//This is where the main menu is defined.
	//Add menu items and init calls here.

	//#############################################
	//standard modules
	#ifdef EN_TEST_MODULE	
		ui.PushItem(F("Sequence"), F("< = 1, > = 2"), SequenceTest);
		ui.PushItem(F("Callback draw"), DrawCallback);
		ui.PushItem(F("tone gen"), ToneGenCallback);
		ui.PushItem(F("A label"), F("Beep on select"), Callback1);
		ui.PushItem(F("Another label"), F("This does nothing"));

		ui.PushItem(F("Parent 1"), F("goto submenu")).SetAsParent('p1');
		ui.PushItem(F("Child 1"), F(" ")).SetParent('p1');
	
		Spin::RegisterTask(SequenceTestTask);
	#endif
}