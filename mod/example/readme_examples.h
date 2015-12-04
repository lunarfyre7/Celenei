/*
 * readme_examples.h
 *
 *  Created on: Dec 3, 2015
 *      Author: Jake Vandereay
 */

#ifndef README_EXAMPLES_H_
#define README_EXAMPLES_H_

#include "../base/modulebase.h"//include the base classes
#include "sol/ui.h"//include the UI class

namespace example_module_1 {

	class MyModule:
			public Module,//include the module base
			public UIcallbackTimer,//include a mixin for adding a UI callback(optional)
			public Spin::Task //include the background task base(optional)
			{
	public:
		MyModule();
		void callback(sol::menucallbackinfo_t &);//your UI callback
		void task();//Your background task
	};

	void setup();
}//example_module_1 end


#endif /* README_EXAMPLES_H_ */
