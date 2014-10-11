#include "module_test.h"
using namespace BEAN;
void sometask(menucallbackinfo_t info) {
	static Timer t;
	if (t.Check(200)) {
		tone(8, 1000, 50);
	}
}