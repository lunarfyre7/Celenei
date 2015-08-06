#include "../config.h"
#include "../ui.h"
#include "../spin.h"
/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#################################################
//include modules here

#ifdef EN_TEST_MODULE
//#include "module_test.h"
#include "examplemodule.h"
namespace mmcb {
	mod_ram ram;
	void ramcb(UI_t::menucallbackinfo_t& info, char** text) {ram.callback(info, text);};
	mod_random rand;
	mod_random rand1;
	mod_random rand2;
	void  randcb(UI_t::menucallbackinfo_t& info, char** text) {rand.callback(info, text);};
	void randcb1(UI_t::menucallbackinfo_t& info, char** text) {rand1.callback(info, text);};
	void randcb2(UI_t::menucallbackinfo_t& info, char** text) {rand2.callback(info, text);};
}
#endif

//#include "module_grow_core.h"

//#################################################

void InitModules() {
	using namespace UI_t;
	using namespace mmcb;
	extern UI ui;
	//#############################################
	//This is where the main menu is defined.
	//Add menu items and init calls here.

	//#############################################
	//standard modules
	#ifdef EN_TEST_MODULE	
		ui.PushItem(F("ram"), ramcb);
		ui.PushItem(F("rand"), randcb);
		ui.PushItem(F("rand"), randcb1);
		ui.PushItem(F("rand"), randcb2);

//		ui.PushItem(F("ram"), RamCallback);
//		ui.PushItem(F("blank"), DummyCB);
//		ui.PushItem(F("blank no cb"));
//		ui.PushItem(F("blank"), DummyCB2);
//		ui.PushItem(F("A very long label that should scroll"), F("A very long info strip that should also scroll"));
//
//		ui.PushItem(F(">Parent 1<"), F("goto submenu")).LinkTo('p1');
//			ui.PushItem(F(">Root<"), F("<<Back<<")).SetParent('p1').LinkTo(-1);
//			ui.PushItem(F("Child 1"), F(" ")).SetParent('p1');
//			ui.PushItem(F("Child 2"), F(" ")).SetParent('p1');
//			ui.PushItem(F("Child 3"), F(" ")).SetParent('p1');
//
//		Spin::RegisterTask(SequenceTestTask);
	#endif
}
