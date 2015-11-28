#include "ui.h"
#include "config.h"
#include <avr/pgmspace.h>
#include "controls.h"

using namespace sol;
using namespace UI_t;
using namespace std;

int Pstrlen(const __FlashStringHelper * str) {return (int) strlen_P(reinterpret_cast<const PROGMEM char *> (str));}
// bool StrinF(const char * s1, const __FlashStringHelper * fstr) {return (strstr_P(s1, reinterpret_cast<const PROGMEM char *> (fstr)) != NULL);}

void blankCallback(menucallbackinfo_t &info, char** text){};

//UI::UI(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
UI::UI(int addr) 
 :sizeX(0)
 ,sizeY(0)
 ,lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
 ,updateScreen(false)
 ,beepOnChange(true)
 ,buttonScrollTimer(0)
 ,currentMenu()
 ,menuIt()

{
		//lcd(rs, en, d4, d5, d6, d7);
		// std::olcdstream lcdout(lcd);
//		UpdateScreen();
		//create main menu
		//HACK: moved to initLCD due to C++ static init and other weird things

}
UI::~UI() {
}
void UI::InitLCD(uint8_t X, uint8_t Y) {
	sizeX = X;
	sizeY = Y;
	lcd.begin(X,Y);

	//other init code

	//create main menu
	PushMenu('root');//create base menu list
//	PushItem(F("sol test"));//create dummy entry
	JumpToMenu(menus.begin()); //load the main menu into the display

//	menuIt = menus.front().list.begin(); //hack: the above should do the same
}
void UI::Task() {
	//fps throttle
	if(!dispRefreshTimer.Every(100))
		return;
	//iterator check
	PLF("UI::Task tick");
	CheckButtons(currentMenu->list, menuIt);
	DrawDisplay(menuIt);

}
UI& UI::PushItem(const __FlashStringHelper* Label) {
	return PushItem(Label, blankCallback);
}
UI& UI::PushItem(const __FlashStringHelper* Label, MenuItemCallback callback) {
	PF("Item pushed: ");
	PL(Label);
	MenuItem item;
	item.Label =  Label;
	item.Info  =  NULL;
	item.callback = callback;
//	item.parent = -1; //set these with the root level;
//	item.asParent = -1;
	item.link = false; //if true selecting item goes to submenu
	menus.front().list.push_back(item);//push into main menu(first element)

	//reset iterator if list was empty
	if (currentMenu->list.size() <= 1)
		JumpToMenu(menus.begin());
	return *this;
}
//UI& UI::SetParent(int name) {
//	menus.front().list.back()//back element of first menu
//			.parent = name; //set parent in element
//	return *this;
//}
UI& UI::LinkTo(int name) {
	//OLD CODE//
	MenuItem &item = menus.front().list.back(); //get last element of first menu
	//assign attributes to menu item
	item.link = true; //set as link
	item.target = name; //target to link to
	return *this;
}
UI& UI::PushMenu(int name) {
	Menu menu;
	menu.id = name;
	menu.parent = 'root';//default root, even for root
	menus.push_back(menu);
	return *this;
}
void UI::UpdateScreen() {
	updateScreen = true;
}
void UI::CheckButtons(std::list<MenuItem> &menu, std::list<MenuItem>::iterator &menuit) {//the target menu list and an iterator for it
	PLF("UI::CheckButtons called");
	if (!CheckItem())//iterator check
		return;
	button = DPad();
	if (button == lastButton) return; //abort if there has not been a new button press
	lastButton = button; //save button state for above check
	if (button == up) {
		if (menuit == menu.begin()) {//if at beginning go to end
			menuit = menu.end(); //set to end
			menuit--;//then move to last element
		}
		else //otherwise decrement
			menuit--;

	} else if (button == down) {
		menuit++;
		if (menuit == menu.end()) //if at end reset to top
			menuit = menu.begin();
	}
}
void UI::DrawDisplay(list<MenuItem>::iterator it) {//draws text lines in menus and calls menu callbacks. 'it' is current menu
	menucallbackinfo_t cbinfo; //this is passed to the callback
	PLF("UI::DrawDisplay called");


	uint8_t y=0;//line index of current line we're writing
	do {
		//abort if list is empty
		if(currentMenu->list.size() == 0) {
			lcd.setCursor(0,0);
			lcd.print(F("menu is empty"));
			return;
		}
		//menu item rollback
		if(it == currentMenu->list.end())
			it = currentMenu->list.begin();

		PF("Item iterator info -- ");
			PF("info: ");
			P(it->Info);
			PF(", label: ");
			PL(it->Label);
		//call the callback
		(*it->callback)(cbinfo, &(it->Info));
		PLF("callback");
		//clear and write line
		ClearSection(0, y, sizeX, lcd);
		lcd.setCursor(0,y); //set line to y
		if(menuIt == it)//write arrow on selected line
			lcd.write(0x7E);
		else//or space on the others
			lcd.setCursor(1,y);
		//print label and callback string
		lcd.print(it->Label);
		PLF("label");
		lcd.print(it->Info); //string from the callback
		PLF("info");

		//increment y and it and check for end of screen
		y++; it++;
	} while(y != LCD_Y);//break when we get to the end of the screen
}
void UI::JumpToMenu(list<Menu>::iterator menu) {//set current menu and request redraw.
	PLF("UI::JumpToMenu");
	currentMenu = menu;
	PLF("menu ids: ");
	P(menu->id);
	PF(" & ");
	PL(currentMenu->id);
	PF("menu list length: ");
	PL(menu->list.size());
	menuIt = currentMenu->list.begin(); //set it. to the new menu
	UpdateScreen();
	PLF("UI::JumpToMenu END");
}

bool UI::CheckItem() {
	//return true if errors are not found, otherwise false
	return !(currentMenu->list.size() == 0 || menuIt == currentMenu->list.end());
}
