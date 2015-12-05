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

}//ns cel

class Module;
class UIcallback {
protected:
	char *text_store; //storage for dynamic ui text
	void ptrset(char **);//points the text pointer pointer to the string pointer.
	void alloc(uint8_t len);//call from constructor if using ui callback. len is the length of the ui string
public:
	UIcallback();
	virtual ~UIcallback();
	virtual void callback (cel::menucallbackinfo_t& info) =0;//implement your UI callback as this
	virtual void proxy(cel::menucallbackinfo_t& info, char** text);//called by the UI system
};
class UIcallbackTimer : public UIcallback {//adds auto refresh timing to the callback
	cel::Timer u_timer;//update timer
	uint16_t period;
public:
	UIcallbackTimer(uint16_t);//pass the refresh time here
	void proxy(cel::menucallbackinfo_t& info, char** text);
};


#endif /* UITYPES_H_ */
