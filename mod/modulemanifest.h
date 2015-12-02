/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#define IS_MOD_MANIFEST //for module registration
//include modules here into this namespace
#include "example/examplemodule.h"
#include "bundled/UItester.h"

void module_setup() {
	//add setup calls here
	example_module::setup();
	selfTest::setup();
}
