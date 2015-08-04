#include "ui.h"
#include "config.h"
#include <avr/pgmspace.h>
#include "buffer.h"


using namespace UI_t;

#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir_t DPad() {

  int reading = analogRead(BUTTON_PIN);
  //Serial.print(F("dpad val: ")); Serial.println(reading); //uncomment for recalibration info
  btndir_t val;
  					 val = up;
  if (reading < 750) val = left;
  if (reading < 655) val = center;
  if (reading < 440) val = down;
  if (reading < 265) val = right;
  if (reading < 100) val = none;
  return val;
}
#endif

int Pstrlen(const __FlashStringHelper * str) {return (int) strlen_P(reinterpret_cast<const PROGMEM char *> (str));}
// bool StrinF(const char * s1, const __FlashStringHelper * fstr) {return (strstr_P(s1, reinterpret_cast<const PROGMEM char *> (fstr)) != NULL);}

void blankCallback(menucallbackinfo_t info, char** text){};

//UI::UI(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
UI::UI(int addr) 
 :sizeX(0)
 ,sizeY(0)
 ,currentMenuItem(0)
 ,lastMenuItem(0)
 ,lcd(LCD_I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
 ,updateScreen(false)
 ,beepOnChange(true)
 ,menuLevel(-1)
 ,buttonScrollTimer(0)
{
		//lcd(rs, en, d4, d5, d6, d7);
		// std::olcdstream lcdout(lcd);
		InitBuffer();
		UpdateScreen();
}
UI::~UI() {
	DestroyBuffer();
}
void UI::InitLCD(uint8_t X, uint8_t Y) {
	sizeX = X;
	sizeY = Y;
	lcd.begin(X,Y);
}
void UI::Task() {
	// if(dispRefreshTimer.Check(LCD_REFRESH_TIME)) {//handle display
	if(DoUpdateScreen()) {//handle display
		//if (Pstrlen(menu[currentMenuItem].Info) > 0)  {
//			ClearSection(0,0,sizeX, lcd);
//			lcd.print(menu[currentMenuItem].Info);
		//}
		ClearSection(0,0,sizeX, lcd);
		lcd.setCursor(0,0);
		//TODO add text scrolling for large labels
//		lcd.setCursor((sizeX - Pstrlen(menu[currentMenuItem].Label))/2, 1);//center label
		lcd.print(menu[currentMenuItem].Label);
		lcd.print(menu[currentMenuItem].Info);
	}
	if (scrollTimer.Check(400)) {//basic scrolling
	}
	if(buttonTimer.Check(BUTTONCHECK_TIME)) {//handle button presses
		menucallbackinfo_t cbInfo = NOTHING;
		btndir_t button = DPad();
		if (button == none) {
			buttonScrollTimer = millis();
		}
		if (lastButtonState == none || buttonScrollTimer + SCROLL_THRESHHOLD < millis()){
			buttonScrollTimer += SCROLL_STEP;
			//Menu item navigation
			do {
				if (button == up) {
					currentMenuItem = currentMenuItem == 0 ? menu.size() -1 : currentMenuItem - 1;//loop it around from the beginning, would be easier to use signed int.
				} else if (button == down) {
					currentMenuItem++;
					currentMenuItem = currentMenuItem % menu.size(); //limit the index
				}
			} while(menu[currentMenuItem].parent != menuLevel);//ignore those in a different level. could get stuck
			//callback buttons
			if (lastMenuItem != currentMenuItem) {
				UpdateScreen();
				if (beepOnChange) tone(SPEAKER_PIN, 1000, 30);
				cbInfo = NEW;
			} else if (button == left) {
				cbInfo = LEFT;
			} else if (button == right) {
				cbInfo = RIGHT;
			} else if (button == center) {
				cbInfo = SELECT;
				if (menu[currentMenuItem].link && menu[currentMenuItem].asParent != menuLevel) {
						menuLevel = menu[currentMenuItem].asParent;
						RefreshMenu();
					}
			}
			lastMenuItem = currentMenuItem;
		}
		lastButtonState = button;
		(*menu[currentMenuItem].callback)(cbInfo, &menu[currentMenuItem].Info);
	}
}
UI& UI::PushItem(const __FlashStringHelper* Label) {
	return PushItem(Label, blankCallback);
}
UI& UI::PushItem(const __FlashStringHelper* Label, MenuItemCallback callback) {
	MenuItem item;
	item.Label =  Label;
	item.Info  =  NULL;
	item.callback = callback;
	item.parent = -1; //set these with the root level;
	item.asParent = -1;
	item.link = false; //if true selecting item goes to submenu
	menu.push_back(item);
	return *this;
}
UI& UI::SetParent(int name) {
	menu.back().parent = name;
	return *this;
}
UI& UI::LinkTo(int name) {
	menu.back().asParent = name;
	menu.back().link = true;
	return *this;
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
void UI::RefreshMenu() {
	currentMenuItem = 0;
	while(menu[currentMenuItem].parent != menuLevel && currentMenuItem < menu.size()) {
		currentMenuItem++;
	}
	UpdateScreen();
}
void UI::InitBuffer() {
	buffer = new char* [sizeX];
	for (int i = 0; i < sizeX; ++i)
	{
		buffer[i] = new char[sizeY];
	}
}
void UI::DestroyBuffer() {
	for (int i = 0; i < sizeX; ++i)
	{
		delete buffer[i];
	}
	delete buffer;
}
template <typename T>
int8_t UI::Bprint(T in) {
	return 0; //unimplemented
}
