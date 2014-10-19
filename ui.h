#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal.h>
#include <lcdostream>
#include <iterator>
#include <vector>
#include "timer.h"

namespace UI_t {
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

typedef void(*MenuItemCallback)(UI_t::menucallbackinfo_t);
struct MenuItem{
	const __FlashStringHelper* Label;
	const __FlashStringHelper* Info;
	MenuItemCallback callback;

	const __FlashStringHelper* parent;
	const __FlashStringHelper* asParent;
};
class UI {
public:
	//Constructor
	UI(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	void Task();//start this as a task
	
	//data manipulation and stuff
	UI PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info);
	UI PushItem(const __FlashStringHelper* Label, MenuItemCallback); //use this form for callback's that draw on line 1;
	UI PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback);
	
	void SetParent(const __FlashStringHelper*);
	void SetAsParent(const __FlashStringHelper*);

	//screen
	//Must be called before task is started!
	void InitLCD(uint8_t X, uint8_t Y);
	void UpdateScreen();

	LiquidCrystal lcd;

	//pub vars
	bool beepOnChange;
private:
	uint8_t sizeX, sizeY;
	// std::olcdstream lcdout;
	std::vector<MenuItem> menu;
	unsigned int currentMenuItem;
	Timer dispRefreshTimer;
	Timer buttonTimer;
	UI_t::btndir_t lastButtonState;
	unsigned int lastMenuItem;
	int lastInsertedMenuItem;
	bool updateScreen;

	//methods
	bool DoUpdateScreen();
};

#endif