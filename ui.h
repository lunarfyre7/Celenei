#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal.h>
#include <lcdostream>
#include <iterator>
#include <vector>
#include "timer.h"

namespace BEAN {
	enum menucallbackinfo_t {
		NEW, //menu entry has just been selected
		NOTHING, //no buttons pressed
		SELECT, //user has just eaten cake
		LEFT, 
		RIGHT
	};
	enum btndir_t {
		up,
		down, 
		left,
		right,
		center,
		none
	};
}

typedef void(*MenuItemCallback)(BEAN::menucallbackinfo_t);
struct MenuItem{
	const __FlashStringHelper* Label;
	const __FlashStringHelper* Info;
	MenuItemCallback callback;
};
class UI {
public:
	//Constructor
	UI(uint8_t X, uint8_t Y);
	void Task();//start this as a task
	
	//data manipulation and stuff
	void PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info);
	void PushItem(const __FlashStringHelper* Label, MenuItemCallback); //use this form for callback's that draw on line 1;
	void PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback);
	
	void UpdateScreen();

	LiquidCrystal lcd;
private:
	uint8_t sizeX, sizeY;
	// std::olcdstream lcdout;
	std::vector<MenuItem> menu;
	unsigned int currentMenuItem;
	Timer dispRefreshTimer;
	Timer buttonTimer;
	BEAN::btndir_t lastButtonState;
	unsigned int lastMenuItem;
	bool updateScreen;

	//methods
	bool DoUpdateScreen();
};

#endif