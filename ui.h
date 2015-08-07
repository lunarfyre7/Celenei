#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <lcdostream>
#include <iterator>
#include <vector>
#include "timer.h"

namespace UI_t {
	struct menucallbackinfo_t {
		bool _new; //menu entry has just been selected
		bool nothing; //no buttons pressed
		bool select; //user has just eaten cake
		bool left;
		bool right;
		int  menuindex;
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

typedef void(*MenuItemCallback)(UI_t::menucallbackinfo_t&, char**);//TODO use lambdas instead of this
struct MenuItem{
	const __FlashStringHelper* Label;
	char* Info;
	MenuItemCallback callback;

	int parent;
	int asParent;
	bool link;
};
class UI {
public:
	//Constructor
	//UI(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
	UI(int);
	~UI();
	void Task();//start this as a task
	
	//Menu insertion & manipulation
	UI& PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info);
	UI& PushItem(const __FlashStringHelper* Label);
	UI& PushItem(const __FlashStringHelper* Label, MenuItemCallback); //use this form for callback's that draw on line 1;
	UI& PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback);
	
	UI& SetParent(int name); //both take multi character literals, e.g., 'abc'
	UI& LinkTo(int name);

	//screen
	void InitLCD(uint8_t X, uint8_t Y);//Must be called before task is started!
	void UpdateScreen();

	LiquidCrystal_I2C lcd;

	//pub vars
	bool beepOnChange;
private:

	uint8_t sizeX, sizeY;
//	Timer dispRefreshTimer;
	Timer buttonTimer;
//	Timer scrollTimer;
	// std::olcdstream lcdout;
	std::vector<MenuItem> menu;
	unsigned int currentMenuItem; //current menu item index
	unsigned int screenPos;
	UI_t::btndir_t lastButtonState;
	unsigned int lastMenuItem;
	int menuLevel; //current menu parent
	unsigned long buttonScrollTimer;
	bool updateScreen; //true if screen needs update
	char ** buffer;

	//methods
//	bool DoUpdateScreen();
	void RefreshMenu(); //called after changing menu level
	void InitBuffer();
	void DestroyBuffer();
	template <typename T>
	int8_t  Bprint(T);
};

#endif
