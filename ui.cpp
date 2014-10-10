#include "ui.h"

enum btndir {
	up,
	down, 
	left,
	right,
	center,
	none
};

#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir DPad() {
  //0 = no buttons pressed
  //1 = up
  //2 = down
  //3 = left
  //4 = right
  //5 = center
  int reading = analogRead(BUTTONPIN);
  btndir val;
  if (reading < 1000) val = up;
  if (reading < 720) val = left;
  if (reading < 620) val = center;
  if (reading < 350) val = down;
  if (reading < 200) val = right;
  if (reading < 5) val = none;
  return val;
}
#endif

void BlankCallback(){};

UI::UI(uint8_t X, uint8_t Y) 
 :sizeX(X)
 ,sizeY(Y)
 ,currentMenuItem(0)
 ,lcd(11,10,5,4,3,2)
{
		// LiquidCrystal lcd(11,10,5,4,3,2);
		lcd.begin(16,2);
		// std::olcdstream lcdout(lcd);
}
void UI::Task() {
	if(dispRefreshTimer.Check(LCD_REFRESH_TIME)) {
		lcd.clear();
		lcd.print(menu[currentMenuItem].Label);
	}
	if(buttonTimer.Check(BUTTONCHECK_TIME)) {
		btndir button = DPad();
		if (button == up) {
			currentMenuItem--;
		} else if (button == down) {
			currentMenuItem++;
		}
		currentMenuItem = currentMenuItem % menu.size(); //limit the index of currentmenuitem
	}
}
void UI::PushItem(const char* Label, const char* Info) {
	MenuItem item;
	item.Label =  Label;
	item.Info  =  Info;
	menu.push_back(item);
}
