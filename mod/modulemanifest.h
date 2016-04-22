/*
###################################################
#                Module Manifest                  #
###################################################
*/
//#define IS_MOD_MANIFEST //for module registration
//include modules here
#include "example/examplemodule.h"
//#include "bundled/UItester.h"
#include "example/snake.h"

void module_setup() {
	//add setup calls here
	example_module::setup();
	mod_snake::setup();

}
