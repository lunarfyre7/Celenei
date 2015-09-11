/*
 * Settings.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: Jake
 */

#include "Settings.h"
#include "config.h"
#include <avr/eeprom.h>

using namespace sol;
using namespace std;


Settings::Settings() {
	Read();
}

Settings::~Settings() {
}
void Settings::Register(char name[], int val) {
	setting_t sett;
	sett.val = val;
	sett.hash = StrHash(name);
	intlist.push_back(sett);
	Save();
}
void Settings::Set(char name[], int val) {
	int index = Find(StrHash(name));
	if (index == -1)
		Register(name, val);
	else {
		intlist[index].val = val;
		Save();
	}
}
int  Settings::Get(char name[]) {
	int index = Find(StrHash(name));
	return intlist[index].val;
}
int Settings::Find(int hash) {
	for(std::vector<setting_t>::iterator it=intlist.begin(); it != intlist.end(); it++)
		if(it->hash == hash)
			return std::distance(intlist.begin(), it);
	return -1;
}
int Settings::StrHash(char string[]) {
	int hash = SEED; //seed
	int len = sizeof(string)/sizeof(string[0]);
	for(int i=0;i<len;i++)
		hash *= (int) string[i];
	return hash;
}
int Settings::IntHash(int num) {
	int hash = SEED; //seed
	do {
		hash *= num && 0x0f;
		num = num >> 0x0f;
	} while(num > 0);
	return hash;
}
void Settings::Save() {
	int pos = 0;
	uint8_t size = sizeof(int)/sizeof(uint8_t);
	for(std::vector<setting_t>::iterator it=intlist.begin(); it != intlist.end(); it++) {
		if(eeprom_read_word((uint16_t*)&pos) != it->hash)
			eeprom_write_word((uint16_t*)&pos, it->hash);
		pos += size;
		if(eeprom_read_word((uint16_t*)&pos) != it->val)
					eeprom_write_word((uint16_t*)&pos, it->val);
		pos += size;
	}
}
void Settings::Read() {
	int pos = 0;
	uint8_t size = sizeof(int)/sizeof(uint8_t);
	int hash, value;
	setting_t tuple;
	do {
		hash = eeprom_read_word((uint16_t*)&pos);
		pos += size;
		value = eeprom_read_word((uint16_t*)&pos);
		pos += size;
		tuple.hash = hash;
		tuple.val = value;
		intlist.push_back(tuple);
	} while (hash != 0);
}
