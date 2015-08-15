/*
 * Modulereg.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: Jake
 */
#include "../utilfn.h"

#include "Modulereg.h"
using namespace std;


list<Module_reg*> Module_reg::flist;
Module_reg::Module_reg(voidfptr_t fptr)
        :function(fptr)
    {
        if (fptr) //skip NULL pointers
            flist.push_back(this);
    }
Module_reg::Module_reg()
        :function(NULL)
        {}
void Module_reg::run(){
	DebugP(F("modreg list len:"));
	Serial.println(flist.size());
    for (list<Module_reg*>::const_iterator iterator = flist.begin(), end = flist.end(); iterator != end; ++iterator) {
        (*iterator)->runf();
    }
}
void Module_reg::runf(){
    if (function)
        (*function)();
}
