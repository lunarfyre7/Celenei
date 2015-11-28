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


//		Menu mainmenu;
//		mainmenu.id = 'main'; //id for the root menu is 'main'
//		menus.push_back(); //add the main menu to the menu list
//		JumpToMenu(&menus.front()); //load the main menu into the display
}
UI::~UI() {
}
void UI::InitLCD(uint8_t X, uint8_t Y) {
	sizeX = X;
	sizeY = Y;
	lcd.begin(X,Y);

	//other init code

	//create main menu
//	Menu mainmenu;
//	mainmenu.id = 'main'; //id for the root menu is 'main'
//	//create blank entry
//	MenuItem headerItem;
//	headerItem.Label = F("Initial item");
//	mainmenu.list.push_back(headerItem);
//	menus.push_back(mainmenu); //add the main menu to the menu list
	PushMenu('root');//create base menu list
	PushItem(F("sol test"));//create dummy entry
	JumpToMenu(menus.begin()); //load the main menu into the display

//	menuIt = menus.front().list.begin(); //hack: the above should do the same
}
void UI::Task() {
//	menucallbackinfo_t cbInfo;
////	cbInfo.nothing = true;
//	btndir_t button = DPad();
//	//abort if no menu items
//	if (menu.size() == 0)
//		return;
//	if (button == none) {
//		buttonScrollTimer = millis();
//	}
//	if (lastButtonState == none || buttonScrollTimer + SCROLL_THRESHHOLD < millis()){
//		buttonScrollTimer += SCROLL_STEP;
//		//Menu item navigation
//		do {
//			if (button == up) {
//				currentMenuItem = currentMenuItem == 0 ? menu.size() -1 : currentMenuItem - 1;//loop it around from the beginning, would be easier to use signed int.
//			} else if (button == down) {
//				currentMenuItem++;
//				currentMenuItem = currentMenuItem % menu.size(); //limit the index
//			}
//		}
////		while(menu[currentMenuItem].parent != menuLevel);//ignore those in a different level. could get stuck
//		//callback buttons
//		if (lastMenuItem != currentMenuItem) {
////			cbInfo.nothing = false;
//			UpdateScreen();
//			if (beepOnChange) tone(SPEAKER_PIN, 1000, 30);
//			cbInfo._new = true;
//		}
//		if (button == center) {
//			if (menu[currentMenuItem].link && menu[currentMenuItem].asParent != menuLevel) {
//					menuLevel = menu[currentMenuItem].asParent;
//					RefreshMenu();
//				}
//		}
//		lastMenuItem = currentMenuItem;
//	}
//	lastButtonState = button;
//	for (uint8_t y=0;y<LCD_Y;y++) {
////			uint8_t index = (currentMenuItem+y) % menu.size();
//		if(currentMenuItem > screenPos + LCD_Y-1){//past bottom
//			screenPos = (screenPos+1)%menu.size();
////				updateScreen = true;
//		}
//		else if (currentMenuItem < screenPos)//past top
//			screenPos = (screenPos-1)%menu.size();
//		uint8_t index = (screenPos+y) % menu.size();//maybe a bad place for this
//		while(menu[index].parent != menuLevel) {index++;screenPos++;}//HACK move screen pos forward if element is not from same parent
//		cbInfo.menuindex = (int)index;
//		if(currentMenuItem == index) {//give more into to selected callback
//			cbInfo.isSelected = true;
//			cbInfo.button = DPad();
//		} else {
//			cbInfo.isSelected = false;
//			cbInfo.button = none;
//		}
//		(*menu[index].callback)(cbInfo, &(menu[index].Info));
//		if(updateScreen) {//handle display
//			ClearSection(0,y,sizeX, lcd);
//			lcd.setCursor(0,y);
//			//print pointer icon
//			if(currentMenuItem == index)//print arrow on current selection
//				lcd.write(0x7E);
//			else
//				lcd.setCursor(1,y);
//			lcd.print(menu[index].Label);
//			lcd.print(menu[index].Info);
//			#ifdef DEBUG_INFO
//			//index     currentMenuItem
//			//menu.size screenPos
//			lcd.setCursor(LCD_X-4, 0);
//			lcd.print(index);
//			lcd.setCursor(LCD_X-2, 0);
//			lcd.print(currentMenuItem);
//			lcd.setCursor(LCD_X-2, 1);
//			lcd.print(screenPos);
//			lcd.setCursor(LCD_X-4, 1);
//			lcd.print(menu.size());
//			#endif
//		}
//	}
//	updateScreen = false;
	//fps throttle
	if(!dispRefreshTimer.Every(100))
		return;
	//iterator check
	if (menuIt == currentMenu->list.end()) { //if menu is empty
		lcd.setCursor(0,0);
		PLF("warning, empty menu");
		lcd.print(F("No items"));
		return;
	}
	PLF("UI::Task tick");
	CheckButtons(currentMenu->list, menuIt);
	DrawDisplay(menuIt);

}
UI& UI::PushItem(const __FlashStringHelper* Label) {
	return PushItem(Label, blankCallback);
}
UI& UI::PushItem(const __FlashStringHelper* Label, MenuItemCallback callback) {
	MenuItem item;
	item.Label =  Label;
	item.Info  =  NULL;
	item.callback = callback;
//	item.parent = -1; //set these with the root level;
//	item.asParent = -1;
	item.link = false; //if true selecting item goes to submenu
	menus.front().list.push_back(item);//push into main menu(first element)
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
	button = DPad();
	if (button == lastButton) return; //abort if there has not been a new button press
	lastButton = button; //save button state for above check
	if (button == up) {
		if (menuit == menu.begin())//if at beginning go to end
			menuit = menu.end();
		else //otherwise decrement
			menuit--;

	} else if (button == down) {
		if (menuit == menu.end()) //if at end reset to top
			menuit = menu.begin();
		else //otherwise increment
			menuit++;
	}
}
void UI::DrawDisplay(list<MenuItem>::iterator it) {//draws text lines in menus and calls menu callbacks. 'it' is current menu
	menucallbackinfo_t cbinfo; //this is passed to the callback
	PLF("UI::DrawDisplay called");


	uint8_t y=0;//line index of current line we're writing
	do {
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
	} while(y != LCD_Y && it != currentMenu->list.end());//break when we get to the end of the screen or reach the end of the list
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
