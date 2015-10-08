/*
 * Settings.h
 *
 *  Created on: Sep 8, 2015
 *      Author: Jake
 */
#include <iterator>
#include <vector>
#include <stddef.h>

#ifndef SETTINGS_H_
#define SETTINGS_H_
namespace sol { //TODO wrap all core classes in this namespace
	struct setting_t {
		unsigned int val;
		unsigned int hash;
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
		unsigned int StrHash(char string[]);
		unsigned int IntHash(int);
		int Find(unsigned int);
	};
}
#endif /* SETTINGS_H_ */
