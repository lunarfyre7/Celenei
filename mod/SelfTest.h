/*
 * SelfTest.h
 *
 *  Created on: Sep 9, 2015
 *      Author: Jake
 */

#ifndef SELFTEST_H_
#define SELFTEST_H_

#include "base/Modulereg.h"

namespace test {

void SettingTest();


#ifdef IS_MOD_MANIFEST
static void wrapper() {
//	SettingTest();
}

Module_reg wrapper_object(wrapper);
#endif //IS_MOD_MANIFEST
} /* namespace test */

#endif /* SELFTEST_H_ */
