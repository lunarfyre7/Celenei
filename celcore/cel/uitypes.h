/*
 * uitypes.h
 *
 *  Created on: Dec 3, 2015
 *      Author: Jake Vandereay
 */

#ifndef UITYPES_H_
#define UITYPES_H_


namespace cel {
	struct menucallbackinfo_t {
		bool _new; //menu entry has just been selected
		bool isSelected; //is the current menu item;
		btndir_t button; //the button state
		int  menuindex;
	};
}


#endif /* UITYPES_H_ */
