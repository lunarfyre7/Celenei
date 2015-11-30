/*
###################################################
#                Module Manifest                  #
###################################################
*/
//include modules here
//#define IS_MOD_MANIFEST //for module registration
#include "example/examplemodule.h"

void module_setup() {
	//add setup calls here
	example_module::setup();
}
