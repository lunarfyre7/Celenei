/*
 * Modulereg.h
 *
 *  Created on: Aug 12, 2015
 *      Author: Jake
 */
//#include "../fw_main.h"
#include <iterator>
#include <list>
#include "../config.h"
//#include "modulebase.h"

#ifndef MODULEREG_H_
#define MODULEREG_H_
typedef void (*voidfptr_t)();
class Module_reg {
public:
	Module_reg();
	Module_reg(voidfptr_t);
//    static int push(voidfptr_t fptr);
    static void run();
    void runf();
    voidfptr_t function;
    static std::list<Module_reg*> flist;
	static void test();
};

#endif /* MODULEREG_H_ */
