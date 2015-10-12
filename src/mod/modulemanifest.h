/*
###################################################
#                Module Manifest                  #
###################################################
*/
//include modules here
#include "examplemodule.h"
#include "SelfTest.h".h"


//#################################################
//old setup code
//void InitModules() {
//	using namespace UI_t;
//	using namespace mmcb;
//	extern UI ui;
//	//#############################################
//	//This is where the main menu is defined.
//	//Add menu items and init calls here.
//
//	//#############################################
//	//standard modules
//	#ifdef EN_TEST_MODULE
//		//root menu
//		Module_base *mod_base = new Module_base;
//		mod_base.ext_wrapper = *basecb;
//		ui.PushItem(F("blank"));
//		mod_base.setup_all();
//		mod_base->setup(&ui);
//		ui.PushItem(F("rand0"), randcb);
//		ui.PushItem(F("ram"), ramcb);
//		ui.PushItem(F("lag"), lagcb);
//		ui.PushItem(F(">Random<")).LinkTo('rnd');
//		ui.PushItem(F(">Parent 1<")).LinkTo('p1');
//
//		//demo sub menu
//			ui.PushItem(F(">Root<")).SetParent('p1').LinkTo(-1);
//			ui.PushItem(F("Child 1")).SetParent('p1');
//			ui.PushItem(F("Child 2")).SetParent('p1');
//			ui.PushItem(F("Child 3")).SetParent('p1');
//
//		//random gen submenu
//		//place sub items after root items, somewhat of a bug/laziness
//		//TODO fix menu logic to make this not necessary. (sort)
//			ui.PushItem(F(">Root<")).SetParent('rnd').LinkTo(-1);
//			ui.PushItem(F("rand0"), randcb).SetParent('rnd');
//			ui.PushItem(F("rand1"), randcb1).SetParent('rnd');
//			ui.PushItem(F("rand2"), randcb2).SetParent('rnd');
//	#endif
//}
