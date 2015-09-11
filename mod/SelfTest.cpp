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
	Settings* sett = new Settings;
	sett->Register("setting1", 5);
	sett->Save();
	delete sett;
	Settings* sett2 = new Settings;
	sett2->Read();
	int setting1 = sett2->Get("Setting1");
	ASSERT(setting1 == 5);
	delete sett2;
	Serial.println(F("--Setting test end--"));
}

} /* namespace test */
