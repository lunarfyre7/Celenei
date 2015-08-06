#include "../config.h"
#include "../ui.h"
#include "../spin.h"
#define wrapCB(name,obj) void name(UI_t::menucallbackinfo_t& info, char** text) {obj.callback(info, text);}//make callback wrapper
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
//	void ramcb(UI_t::menucallbackinfo_t& info, char** text) {ram.callback(info, text);};
	wrapCB(ramcb, ram);//Use this to make a wrapper for the callback
	mod_lag lag;
	wrapCB(lagcb, lag);
	mod_random rand; //this uses 27 bytes
	mod_random rand1;
	mod_random rand2;
	wrapCB(randcb, rand);
	wrapCB(randcb1, rand1);
	wrapCB(randcb2, rand2);
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
		ui.PushItem(F("lag"), lagcb);
		ui.PushItem(F("rand"), randcb);
		ui.PushItem(F("rand"), randcb1);
		ui.PushItem(F("rand"), randcb2);

//		ui.PushItem(F("ram"), RamCallback);
//		ui.PushItem(F("blank"), DummyCB);
//		ui.PushItem(F("blank no cb"));
//		ui.PushItem(F("blank"), DummyCB2);
//		ui.PushItem(F("A very long label that should scroll"), F("A very long info strip that should also scroll"));
//
		ui.PushItem(F(">Parent 1<")).LinkTo('p1');
			ui.PushItem(F(">Root<")).SetParent('p1').LinkTo(-1);
			ui.PushItem(F("Child 1")).SetParent('p1');
			ui.PushItem(F("Child 2")).SetParent('p1');
			ui.PushItem(F("Child 3")).SetParent('p1');
//
//		Spin::RegisterTask(SequenceTestTask);
	#endif
}
