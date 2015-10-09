/*
 * Settings.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: Jake
 */

#include "Settings.h"
#include "config.h"
//#include <EEPROM.h>
#include <avr/eeprom.h>

#define END_SEN 0xdead //end sentinel

namespace sol {
using namespace std;

vector<setting_t> Settings::intlist;

Settings::Settings() {
//	Read();
}

Settings::~Settings() {
}
void Settings::Register(char name[], int val) {
	setting_t sett;
	sett.val = val;
	sett.hash = StrHash(name);
	//TODO check for setting before pushing to list
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
int Settings::Find(unsigned int hash) {
	for(std::vector<setting_t>::iterator it=intlist.begin(); it != intlist.end(); it++)
		if(it->hash == hash)
			return std::distance(intlist.begin(), it);
	return -1;
}
unsigned int Settings::StrHash(char string[]) {
	unsigned int hash = SEED; //seed
	int len = sizeof(string)/sizeof(string[0]);
	for(int i=0;i<len;i++)
		hash *= (int) string[i];
	return hash;
}
unsigned int Settings::IntHash(int num) {
	unsigned int hash = SEED; //seed
	do {
		hash *= num && 0x0f;
		num = num >> 0x0f;
	} while(num > 0);
	return hash;
}
void Settings::Save() {
	uint16_t pos = 0, buffer;
	uint8_t size = sizeof(int)/sizeof(uint8_t);
	for(std::vector<setting_t>::iterator it=intlist.begin(); it != intlist.end(); it++) {
		//hash write
		buffer = eeprom_read_word((uint16_t*)pos); //cache value from eeprom
		if(buffer != it->hash) {
			eeprom_write_word((uint16_t*)pos, it->hash);
			Serial.println(F("hash saved"));
			Serial.print(it->hash);
			Serial.print(F(" <> "));
			Serial.println(buffer);
		}
		else
			Serial.println(F("hash write skipped"));
		//value write
		pos += size;
		buffer = eeprom_read_word((uint16_t*)pos); //cache value from eeprom
		if(buffer != it->val) {
			eeprom_write_word((uint16_t*)pos, it->val);
//			EEPROM.write(pos, it->val);
			Serial.println(F("val saved"));
			Serial.print(it->val);
			Serial.print(F(" <> "));
			Serial.println(buffer);
		}
		else
			Serial.println(F("val write skipped"));
		pos += size;
	}
	//write end sentinel
	eeprom_write_word((uint16_t*)pos, END_SEN);
}
void Settings::Read() {
	int pos = 0;
	uint8_t size = sizeof(int)/sizeof(uint8_t);
	uint16_t hash, value;
	setting_t tuple;
	//clear setting in ram
	intlist.clear();
	Serial.println(F("Begin read loop"));
	while(pos < 512) {
		hash = eeprom_read_word((uint16_t*)pos);
		Serial.print(F("EEPROM pos: "));
		Serial.println(pos);
		Serial.print(F("stored hash: "));
		Serial.println(hash);
		if (hash == END_SEN || hash == 0)
			break;
		pos += size;
		value = (int)eeprom_read_word((uint16_t*)pos);
		pos += size;
		Serial.print(F("EEPROM pos: "));
		Serial.println(pos);
		Serial.print(F("stored value: "));
		Serial.println(value);
		tuple.hash = hash;
		tuple.val = value;
		intlist.push_back(tuple);
	}
	Serial.println(F("End read loop"));
}

}//ns sol
