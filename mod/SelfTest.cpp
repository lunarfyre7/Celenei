/*
 * SelfTest.cpp
 *
 *  Created on: Sep 9, 2015
 *      Author: Jake
 */

#include "SelfTest.h"
#include "../Settings.h"
#include "../utilfn.h"

namespace test {
using namespace sol;

SelfTest::SelfTest() {
	// TODO Auto-generated constructor stub

}

SelfTest::~SelfTest() {
	// TODO Auto-generated destructor stub
}
void SelfTest::SettingTest() {
	Serial.println(F("--Setting test begin--"));
	Settings sett;
	sett.Register("setting1", 5);
	sett.Save();
	delete sett;
	Settings sett;
	sett.Read();
	int setting1 = sett.Get("Setting1");
	ASSERT(setting1 == 5);
	Serial.println(F("--Setting test end--"));
}

} /* namespace test */
