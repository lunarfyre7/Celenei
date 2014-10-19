#include "ui.h"
#include "config.h"
#include <avr/pgmspace.h>

using namespace UI_t;

#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir_t DPad() {

  int reading = analogRead(BUTTON_PIN);
  btndir_t val;
  if (reading < 1000) val = up;
  if (reading < 720) val = left;
  if (reading < 620) val = center;
  if (reading < 350) val = down;
  if (reading < 200) val = right;
  if (reading < 50) val = none;
  return val;
}
#endif

int Pstrlen(const __FlashStringHelper * str) {return (int) strlen_P(reinterpret_cast<const PROGMEM char *> (str));}
// bool StrinF(const char * s1, const __FlashStringHelper * fstr) {return (strstr_P(s1, reinterpret_cast<const PROGMEM char *> (fstr)) != NULL);}

void BlankCallback(menucallbackinfo_t info){};

UI::UI(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
 :sizeX(0)
 ,sizeY(0)
 ,currentMenuItem(0)
 ,lastMenuItem(0)
 ,lcd(rs, en, d4, d5, d6, d7)
 ,updateScreen(false)
 ,beepOnChange(true)
 ,menuLevel(-1)
{
		//lcd(rs, en, d4, d5, d6, d7);
		// std::olcdstream lcdout(lcd);
		UpdateScreen();
}
void UI::InitLCD(uint8_t X, uint8_t Y) {
	sizeX = X;
	sizeY = Y;
	lcd.begin(X,Y);
}
void UI::Task() {
	// if(dispRefreshTimer.Check(LCD_REFRESH_TIME)) {//handle display
	if(DoUpdateScreen()) {//handle display
		if (Pstrlen(menu[currentMenuItem].Info) > 0)  {
			ClearSection(0,0,sizeX, lcd); //CHANGEME
			lcd.print(menu[currentMenuItem].Info);
		} 
		ClearSection(0,1,sizeX, lcd); //CHANGEME
		//TODO add text scrolling for large labels
		lcd.setCursor((sizeX - Pstrlen(menu[currentMenuItem].Label))/2, 1);//center label
		lcd.print(menu[currentMenuItem].Label);
	}
	menucallbackinfo_t cbInfo = NOTHING;//not the best place for this I think
	if(buttonTimer.Check(BUTTONCHECK_TIME)) {//handle button presses
		btndir_t button = DPad();

		if (lastButtonState == none && button != none){
			//Menu item navigation
			do {
				if (button == up) {
					//currentMenuItem--;
					currentMenuItem = currentMenuItem == 0 ? menu.size() -1 : currentMenuItem - 1;//loop it around from the beginning, would be easier to use signed int.
				} else if (button == down) {
					currentMenuItem++;
					currentMenuItem = currentMenuItem % menu.size(); //limit the index
				}
			} while(menu[currentMenuItem].parent != menuLevel);//ignore those in a different level
			//callback buttons
			if (lastMenuItem != currentMenuItem) {
				UpdateScreen();
				if (beepOnChange) beep();
				cbInfo = NEW;
			} else if (button == left) {
				cbInfo = LEFT;
			} else if (button == right) {
				cbInfo = RIGHT;
			} else if (button == center) {
				cbInfo = SELECT;
				//goto another menu
				if (menu[currentMenuItem].link && menu[currentMenuItem].asParent != menuLevel) {
					menuLevel = menu[currentMenuItem].asParent;
					//do something to refresh menu here
				}
			}
			lastMenuItem = currentMenuItem;
		}
		lastButtonState = button;
		//callback calling. TODO give callback ways to manipulate info
		(*menu[currentMenuItem].callback)(cbInfo);
	}
}
UI& UI::PushItem(const __FlashStringHelper* Label, MenuItemCallback callback) { //TODO make "Label" lowercase
	return PushItem(Label, F(""), callback);
}
UI& UI::PushItem(const __FlashStringHelper* Label, const __FlashStringHelper*Info) {
	return PushItem(Label, Info, BlankCallback);
}
UI& UI::PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback callback) {
	
	MenuItem item;
	item.Label =  Label;
	item.Info  =  Info;
	item.callback = callback;
	item.parent = -1; //set these with the root level;
	item.asParent = -1;
	item.link = false; //if true selecting item goes to submenu
	menu.push_back(item);
	return *this;
}
void UI::SetParent(int name) {
	menu.back().parent = name;
	menu.back().link = true;
}
void UI::SetAsParent(int name) {
	menu.back().asParent = name;
	menu.back().link = true;
}
void UI::UpdateScreen() {
	updateScreen = true;
}
bool UI::DoUpdateScreen() {
	if (updateScreen) {
		updateScreen = false;
		return true;
	} else	{
		return false;
	}
}