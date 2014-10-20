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
		ui.PushItem(F("A very long label that should scroll"), F("A very long info strip that should also scroll"));

		ui.PushItem(F(">Parent 1<"), F("goto submenu")).LinkTo('p1');
			ui.PushItem(F(">Root<"), F("<<Back<<")).SetParent('p1').LinkTo(-1);
			ui.PushItem(F("Child 1"), F(" ")).SetParent('p1');
			ui.PushItem(F("Child 2"), F(" ")).SetParent('p1');
			ui.PushItem(F("Child 3"), F(" ")).SetParent('p1');
	
		Spin::RegisterTask(SequenceTestTask);
	#endif
}