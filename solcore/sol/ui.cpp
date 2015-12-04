#include "ui.h"
#include "config.h"
#include <avr/pgmspace.h>
#include "controls.h"
//#include "../mod/base/modulebase.h"

using namespace sol;
//using namespace UI_t;
using namespace std;

int Pstrlen(const __FlashStringHelper * str) {return (int) strlen_P(reinterpret_cast<const PROGMEM char *> (str));}
// bool StrinF(const char * s1, const __FlashStringHelper * fstr) {return (strstr_P(s1, reinterpret_cast<const PROGMEM char *> (fstr)) != NULL);}

//void blankCallback(menucallbackinfo_t &info, char** text){};

//UI::UI(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
UI::UI(int addr) 
 :sizeX(0)
 ,sizeY(0)
 ,lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
 ,updateScreen(false)
 ,updateLine(false)
 ,beepOnChange(true)
 ,buttonScrollTimer(0)
 ,currentMenu()
 ,menuIt()
 ,cursorOffset(0)
 ,button()
 ,lastButton()
 ,frozen(false)
 ,dirty(false)
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
void UI::task() {
	//fps throttle
	if(!dispRefreshTimer.Every(LCD_REFRESH_TIME))
		return;
	CheckButtons(currentMenu->list, menuIt);
	DrawDisplay(menuIt);

}
UI& UI::PushItem(const __FlashStringHelper* Label) {
	return PushItem(Label, (UIcallback*)NULL);
}
UI& UI::PushItem(const __FlashStringHelper* Label, UIcallback *callback) {
	PF("Item pushed: ");
	PL(Label);
	MenuItem item(Label, callback);
	menus.front().list.push_back(item);//push into main menu(first element)

	//reset iterator if list was empty
	if (currentMenu->list.size() <= 1)
		JumpToMenu(menus.begin());
	return *this;
}
UI& UI::SetParent(char name) {
	PF("perent set to: ");
	PL(name);
	MenuItem item = menus.front().list.back();//back element of first menu
	menus.front().list.pop_back();//delete it from the list
	//find menu
	Menu& target = FindMenuRef(name);
	target.list.push_back(item);
	return *this;
}

UI& UI::LinkTo(char name) {
	PF("linked to: ");
	PL(name);
	MenuItem &item = menus.front().list.back(); //get last element of first menu
	//assign attributes to menu item
	item.link = true; //set as link
	item.target = name; //target to link to
	Linker * lnkr = new Linker(*this, name);//create a new link handler callback object
	item.cb = lnkr;
	PLF("Linker created");
	return *this;
}
UI& UI::PushMenu(char name) {
	PF("pushed menu: ");
	PL(name);
	Menu menu;
	menu.id = name;
	menu.parent = 'root';//default root, even for root
	//check for conflicting ids
	PLF("Checking for conflicts...");
	if (FindMenuIt(name) == menus.end()) {
		PLF("[warning] Menu name conflict!");//complain
	}
	else
		menus.push_back(menu);
	return *this;
}
void UI::UpdateLine() {
	updateLine = true;
}
void UI::UpdateScreen() {
	updateScreen = true;
}
void UI::CheckButtons(std::list<MenuItem> &menu, std::list<MenuItem>::iterator &menuit) {//the target menu list and an iterator for it
	if (!CheckItem())//iterator check
		return;
	button = DPad();
	if (button == lastButton) return; //abort if there has not been a new button press
	lastButton = button; //save button state for above check
	if (button == up) {
		UpdateScreen();
		//offset incrementing
		if(cursorOffset > 0) {//limit cursor offset to screen size
			cursorOffset--;
		}
		//only change iterator if cursor offset is at limit
		//iterator incrementing
		else if (menuit == menu.begin()) {//if at beginning go to end
			menuit = menu.end(); //set to end
			menuit--;//then move to last element
		}
		else //otherwise decrement
			menuit--;

	} else if (button == down) {
		UpdateScreen();
		if(cursorOffset < LCD_Y-1) {//limit cursor offset to screen size
			cursorOffset++;
		}
		else {//move iterator pos if edge it hit
			menuit++;
			if (menuit == menu.end()) //if at end reset to top
				menuit = menu.begin();
		}
	}
}
void UI::DrawDisplay(list<MenuItem>::iterator it) {//draws text lines in menus and calls menu callbacks. 'it' is current menu
	menucallbackinfo_t cbinfo, blankinfo; //this is passed to the callback

	//draw each line and call item callbacks
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
		if(y == cursorOffset) { //selected line
			cbinfo.isSelected = true; //tell the callback its special and showered with attention
			cbinfo.button = button;//give callback button state
		}
		//call the callback
		if (it->cb != NULL) //check for a null pointer
			it->cb->proxy(cbinfo, &(it->Info));//call the ui callback proxy through the pointer to the module object
		//check if dirty
		if (dirty) {
			dirty = false;//disable dirty flag
			return; //restart (abort)
		}
		if (updateScreen || updateLine){
			//clear and write line
			ClearSection(0, y, sizeX, lcd);
			lcd.setCursor(0,y); //set line to y
			if(y == cursorOffset){ //selected line
				if (it->link)
					lcd.write(0x3E);//link arrow
				else
					lcd.write(0x7E); //write arrow on selected line

			}
			else {//or space on the others
				lcd.setCursor(1,y);
				cbinfo.isSelected = false; //or that it's being ignored
			}
			//print label and callback string
			lcd.print(it->Label);
			lcd.print(it->Info); //string from the callback
			updateLine = false;//mark line as clean
		}

		//increment y and it and check for end of screen
		y++; it++;
		//reset cbinfo
		cbinfo = blankinfo;
	} while(y != LCD_Y);//break when we get to the end of the screen
	updateScreen = false;//mark as clean
}
void UI::JumpToMenu(list<Menu>::iterator menu) {//set current menu and request redraw.
	currentMenu = menu;
	menuIt = currentMenu->list.begin(); //set it. to the new menu
	dirty=true; //mark as dirty
	cursorOffset = 0; //move cursor to top of screen
	UpdateScreen();
}

bool UI::CheckItem() {
	//return true if errors are not found, otherwise false
	return !(currentMenu->list.size() == 0 || menuIt == currentMenu->list.end());
}
Menu& UI::FindMenuRef(char id) {
	return *FindMenuIt(id);
}
list<Menu>::iterator UI::FindMenuIt(char id) {
	PLF("UI::Find()");
	for (list<Menu>::iterator i=menus.begin(); i != menus.end(); i++) {
		P(i->id);
		PF(" <> ");
		PL(id);
		if(i->id == id)
			return i;//menu with id found
	}
	//fail
	PLF("failed");
	return menus.begin();
}

void UI::EraseItem(const __FlashStringHelper *label, char parent) {

}
void UI::EraseMenu(char id) {
	list<Menu>::iterator menu = FindMenuIt(id);
	if (menu != menus.begin())//don't erase root
		menus.erase(menu);
	JumpToMenu(menus.begin());
}

//misc data type constructors
MenuItem::MenuItem(const __FlashStringHelper* Label, UIcallback *cb) :
	Label(Label)
	,cb(cb)
	,Info(NULL)
	,link(false)
	,target('root')
	{}
MenuItem::~MenuItem() {
	//delete cb;//bad juju here
}
//linking callback
UI::Linker::Linker(UI &ui, char id) :UIcallback(), id(id), ui(ui) {}
void UI::Linker::callback(menucallbackinfo_t &info) {
	if (info.button == right || info.button == center) {
		PLF("Link activated");
		for (list<Menu>::iterator i=ui.menus.begin(); i != ui.menus.end(); i++) {
			if (i->id == id) {
				ui.JumpToMenu(i);
				PLF("Linked target found");
				return;
			}
		}
		PLF("Link failed");
	}
}
