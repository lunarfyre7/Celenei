/*
 * UItester.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: Jake Vandereay
 */

#include "UItester.h"
#include "sol/ui.h"
#include "MemoryFree.h"

namespace selfTest {

UItester::UItester() {
	// TODO Auto-generated constructor stub

}

UItester::~UItester() {
	// TODO Auto-generated destructor stub
}

void UItester::testSize() {
	int before, after, beforeMenu, afterMenu;
	PLF("UItester::testSize");
	PF("Size of UI MenuItem class: ");
	PL(sizeof(sol::MenuItem));
	PF("Size of UI class: ");
	PL(sizeof(sol::UI));

	//ram size test
	beforeMenu = freeMemory();
	ui.PushMenu('UItest_');
	before = freeMemory();
	ui.PushItem(F("UItest item")).SetParent('UItest_');
	after = freeMemory();
	PF("real ram usage of adding blank ui item: ");
	PL(before - after);
	ui.EraseMenu('UItest_');
	afterMenu = freeMemory();
	PF("Menu creation/destruction leftovers: ");
	PL(beforeMenu - afterMenu);
	PL(beforeMenu);
	PL(before);
	PL(after);
	PL(afterMenu);
}
void UItester::runTests() {
	testSize();
}
void setup() {
	UItester test;
	test.runTests();
}
} /* namespace selfTest */
