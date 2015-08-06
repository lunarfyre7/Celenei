/*
 * module_unit_testing.h
 *
 *  Created on: Aug 6, 2015
 *      Author: Jake
 */

#ifndef MODULE_UNIT_TESTING_H_
#define MODULE_UNIT_TESTING_H_
#include <MemoryFree.h>
void module_unit_test() {
	///test for ram usage
	Serial.print("Ram before: ");
	Serial.println(freeMemory());
	module_base emptymod(0);
	Serial.print("Ram after: ");
	Serial.println(freeMemory());
}



#endif /* MODULE_UNIT_TESTING_H_ */
