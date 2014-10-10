#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal.h>
#include <lcdostream>
#include <iterator>
#include <vector>
#include "timer.h"

enum menucallbackinfo_t {
	NOTHING,
	SELECT,
	LEFT,
	RIGHT
};
typedef void(*MenuItemCallback)(menucallbackinfo_t);
struct MenuItem{
	const char* Label;
	const char* Info;
};
class UI {
public:
	//Constructor
	UI(uint8_t X, uint8_t Y);
	void Task();//start this as a task
	
	//data manipulation and stuff
	void PushItem(const char* Label, const char* Info);
	
private:
	uint8_t sizeX, sizeY;
	LiquidCrystal lcd;
	// std::olcdstream lcdout;
	std::vector<MenuItem> menu;
	unsigned int currentMenuItem;
	Timer dispRefreshTimer;
	Timer buttonTimer;
};

#endif