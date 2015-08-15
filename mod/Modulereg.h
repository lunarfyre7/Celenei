/*
 * Modulereg.h
 *
 *  Created on: Aug 12, 2015
 *      Author: Jake
 */
#include "../fw_main.h"
#include <list>
//#include "modulebase.h"

#ifndef MODULEREG_H_
#define MODULEREG_H_
typedef void (*voidfptr_t)();
class Module_reg {
public:
	Module_reg(); //create object without registering callback
	Module_reg(voidfptr_t); //register new callback
	virtual ~Module_reg();
	static void test() {DebugP(F("blah"));};
	static void run(); //run all callbacks
//private:
	static std::list<Module_reg*> reglist; //list of callbacks/objects registered
	void runf(); //run callback
	voidfptr_t function; //pointer to callback
};

#endif /* MODULEREG_H_ */
