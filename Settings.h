/*
 * Settings.h
 *
 *  Created on: Sep 8, 2015
 *      Author: Jake
 */
#include "config.h"
#include <iterator>
#include <vector>

#ifndef SETTINGS_H_
#define SETTINGS_H_
namespace sol { //TODO wrap all core classes in this namespace
	struct setting_t {
		int val;
		int hash;
	};
	class Settings {
	public:
		Settings();
		virtual ~Settings();

		void Register(char name[], int val);
		void Set(char name[], int val);
		int  Get(char name[]);
		void Save();
		void Read();
	private:
		static std::vector<setting_t> intlist;
		int StrHash(char string[]);
		int IntHash(int);
		int Find(int);
	};
}
#endif /* SETTINGS_H_ */
