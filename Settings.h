/*
 * Settings.h
 *
 *  Created on: Sep 8, 2015
 *      Author: Jake
 */
#include "config.h"
//#include <list>

#ifndef SETTINGS_H_
#define SETTINGS_H_
namespace sol { //TODO wrap all core classes in this namespace
	class Settings {
	public:
		Settings();
		virtual ~Settings();

		void Register(char name[], uint8_t val);
	private:
//		std::list<*>
	};
}
#endif /* SETTINGS_H_ */
