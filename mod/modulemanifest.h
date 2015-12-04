/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#define IS_MOD_MANIFEST //for module registration
//include modules here
#include "example/examplemodule.h"
#include "bundled/UItester.h"
//#include "example/readme_examples.h"

void module_setup() {
	//add setup calls here
	example_module::setup();
	selfTest::setup();
//	example_module_1::setup();
}
