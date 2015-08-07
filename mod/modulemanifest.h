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
		//root menu
		ui.PushItem(F("ram"), ramcb);
		ui.PushItem(F("lag"), lagcb);
		ui.PushItem(F(">Random<")).LinkTo('rnd');
		ui.PushItem(F(">Parent 1<")).LinkTo('p1');

		//demo sub menu
			ui.PushItem(F(">Root<")).SetParent('p1').LinkTo(-1);
			ui.PushItem(F("Child 1")).SetParent('p1');
			ui.PushItem(F("Child 2")).SetParent('p1');
			ui.PushItem(F("Child 3")).SetParent('p1');

		//random gen submenu
		//place sub items after root items, somewhat of a bug/laziness
		//TODO fix menu logic to make this not necessary.
			ui.PushItem(F(">Root<")).SetParent('rnd').LinkTo(-1);
			ui.PushItem(F("rand0"), randcb).SetParent('rnd');
			ui.PushItem(F("rand1"), randcb1).SetParent('rnd');
			ui.PushItem(F("rand2"), randcb2).SetParent('rnd');
//
//		Spin::RegisterTask(SequenceTestTask);
	#endif
}
