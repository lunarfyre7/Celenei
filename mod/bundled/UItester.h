/*
 * UItester.h
 *
 *  Created on: Dec 2, 2015
 *      Author: Jake Vandereay
 */

#ifndef UITESTER_H_
#define UITESTER_H_
#include "../base/modulebase.h"

namespace selfTest {

class UItester: public Module {
	friend void setup();
public:
	UItester();
	virtual ~UItester();

	void testSize();
	void task(){};
	void runTests();
};

void setup();//module setup function

} /* namespace selfTest */

#endif /* UITESTER_H_ */
