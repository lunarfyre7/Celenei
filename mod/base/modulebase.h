/*
 * modulebase.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake Vandereay
 */

#ifndef MODULEBASE_H_
#define MODULEBASE_H_
#include <iterator>
#include <list>
#include "config.h"
//#include "cel/ui.h"
#include "cel/controls.h"
#include "cel/spin.h"
#include "cel/timer.h"
#include "cel/uitypes.h"

class Module { //TODO add non ui background callbacks
public:
	Module();
	virtual ~Module();
	virtual void task() {} //background/non-ui task
};
#endif /* MODULEBASE_H_ */
