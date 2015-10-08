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

void SettingTest();


#ifndef IS_MOD_DEF
static void wrapper() {
	SettingTest();
}

Module_reg wrapper_object(wrapper);
#endif //IS_MOD_DEF
} /* namespace test */

#endif /* SELFTEST_H_ */
