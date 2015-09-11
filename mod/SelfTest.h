/*
 * SelfTest.h
 *
 *  Created on: Sep 9, 2015
 *      Author: Jake
 */

#ifndef SELFTEST_H_
#define SELFTEST_H_

#include "Modulereg.h"

namespace test {

class SelfTest {
public:
	SelfTest();
	virtual ~SelfTest();
	void SettingTest();
};

#ifndef IS_MOD_DEF
static void wrapper() {
	SelfTest test;
	test.SettingTest();
}

extern Module_reg *wrapper_object;
#endif //IS_MOD_DEF
} /* namespace test */

#endif /* SELFTEST_H_ */
