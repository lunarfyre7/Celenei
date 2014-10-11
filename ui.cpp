#include "ui.h"
#include <avr/pgmspace.h>

using namespace BEAN;

#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir_t DPad() {
  //0 = no buttons pressed
  //1 = up
  //2 = down
  //3 = left
  //4 = right
  //5 = center
  int reading = analogRead(BUTTONPIN);
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

void BlankCallback(menucallbackinfo_t info){};

UI::UI(uint8_t X, uint8_t Y) 
 :sizeX(X)
 ,sizeY(Y)
 ,currentMenuItem(0)
 ,lastMenuItem(0)
 ,lcd(11,10,5,4,3,2)
{
		// LiquidCrystal lcd(11,10,5,4,3,2);
		lcd.begin(16,2);
		// std::olcdstream lcdout(lcd);
}
void UI::Task() {
	if(dispRefreshTimer.Check(LCD_REFRESH_TIME)) {//handle display
		if (strlen_P(reinterpret_cast<const prog_char*> (menu[currentMenuItem].Info)))  {
			ClearSection(0,0,16, lcd); //CHANGEME
			lcd.print(menu[currentMenuItem].Info);
		} 
		lcd.setCursor(15, 0);
		ClearSection(0,1,16, lcd); //CHANGEME
		lcd.print(menu[currentMenuItem].Label);
	}
	menucallbackinfo_t cbInfo = NOTHING;//not the best place for this I think
	if(buttonTimer.Check(BUTTONCHECK_TIME)) {//handle button presses
		btndir_t button = DPad();

		if (lastButtonState == none){
			//Menu item navigation
			if (button == up) {
				//currentMenuItem--;
				currentMenuItem = currentMenuItem == 0 ? menu.size() : currentMenuItem - 1;
			} else if (button == down) {
				currentMenuItem++;
			}
			currentMenuItem = currentMenuItem % menu.size(); //limit the index of currentmenuitem
			//callback buttons
			if (lastMenuItem != currentMenuItem) {
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
