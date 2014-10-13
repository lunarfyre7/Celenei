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
  if (reading < 5) val = none;
  return val;
}
#endif

int Pstrlen(const __FlashStringHelper * str) {return (int) strlen_P(reinterpret_cast<const PROGMEM char *> (str));}

void BlankCallback(menucallbackinfo_t info){};

UI::UI(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
 :sizeX(0)
 ,sizeY(0)
 ,currentMenuItem(0)
 ,lastMenuItem(0)
 ,lcd(rs, en, d4, d5, d6, d7)
 ,updateScreen(false)
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
			ClearSection(0,0,16, lcd); //CHANGEME
			lcd.print(menu[currentMenuItem].Info);
		} 
		ClearSection(0,1,16, lcd); //CHANGEME
		//TODO add text scrolling for large labels
		lcd.setCursor((16 - Pstrlen(menu[currentMenuItem].Label))/2, 1);//center label
		lcd.print(menu[currentMenuItem].Label);
	}
	menucallbackinfo_t cbInfo = NOTHING;//not the best place for this I think
	if(buttonTimer.Check(BUTTONCHECK_TIME)) {//handle button presses
		btndir_t button = DPad();

		if (lastButtonState == none){
			//Menu item navigation
			if (button == up) {
				//currentMenuItem--;
				currentMenuItem = currentMenuItem == 0 ? menu.size() -1 : currentMenuItem - 1;
			} else if (button == down) {
				currentMenuItem++;
			}
			currentMenuItem = currentMenuItem % menu.size(); //limit the index of currentmenuitem
			//callback buttons
			if (lastMenuItem != currentMenuItem) {
				UpdateScreen();
				cbInfo = NEW;
			} else if (button == left) {
				cbInfo = LEFT;
			} else if (button == right) {
				cbInfo = RIGHT;
			} else if (button == center) {
				cbInfo = SELECT;
			}
			lastMenuItem = currentMenuItem;
		}
		lastButtonState = button;
		//callback calling. TODO give callback ways to manipulate info
		(*menu[currentMenuItem].callback)(cbInfo);
	}
}
void UI::PushItem(const __FlashStringHelper* Label, MenuItemCallback callback) {
	PushItem(Label, F(""), callback);
}
void UI::PushItem(const __FlashStringHelper* Label, const __FlashStringHelper*Info) {
	PushItem(Label, Info, BlankCallback);
}
void UI::PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback callback) {
	MenuItem item; //Yes, this is copy and paste code.
	item.Label =  Label;
	item.Info  =  Info;
	item.callback = callback;
	menu.push_back(item);
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