/*
 * persist.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Jake Vandereay
 *
 *  A persistent storage template using eeprom
 */

#ifndef PERSIST_H_
#define PERSIST_H_

#include <avr/eeprom.h>

template <class T> class Persist{ //wrapper for EEMEM variables
public:
	Persist(T *variable_ptr) { //pointer to eemem variable
		store = variable_ptr;
	}
	T get() {//get stored value
		T value;
		eeprom_read_block(&value, store, sizeof(value));
		return value;
	}
	void set (T value) {//set value
		//get stored value
		T old = get();
		//skip writes when new value is the same as old value
		if(old != value)
			eeprom_write_block(&value, store, sizeof(value));//write to eeprom
	}
	void operator=(T value) { //use the = operator as a setter
		set(value);
	}
private:
	T *store; //pointer to eemem variable
};


//macro for persistent variable creation. Creates EEMEM var and wrapper object.
#define PERSIST(type, name) \
	type EEMEM __name; /*create eemem variable*/ \
	Persist<type> name(&__name); /*create interface object*/
//macro with default value
#define PERSIST_D(type, name, default) \
	type EEMEM __name = default; /*create eemem variable*/ \
	Persist<type> name(&__name); /*create interface object*/


#endif /* PERSIST_H_ */
