/*
 * examplemodule.h
 *
 *  Created on: Aug 4, 2015
 *      Author: Jake
 */

#ifndef EXAMPLEMODULE_H_
#define EXAMPLEMODULE_H_

#include "modulebase.h"

class example_module: public module_base {
public:
	example_module();
	virtual ~example_module();
	void callback(UI_t::menucallbackinfo_t&, char**);
private:
	int ram;
	Timer timer;
	char **text;
	char *text_str;
};

#endif /* EXAMPLEMODULE_H_ */
