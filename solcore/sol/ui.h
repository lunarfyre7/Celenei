#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <lcdostream>
//#include <iterator>
#include <list>
#include "timer.h"
#include "controls.h"
#include "sol/spin.h"
//#include "../mod/base/modulebase.h"
class Module;//forward declaration
class UIcallback; //ditto

namespace sol {
	namespace UI_t {
		struct menucallbackinfo_t {
			bool _new; //menu entry has just been selected
			bool isSelected; //is the current menu item;
			btndir_t button; //the button state
			int  menuindex;
		};
	}

//	typedef void(*MenuItemCallback)(UI_t::menucallbackinfo_t&, char**);//TODO use lambdas instead of this
//	typedef void(Module::*MenuItemCallback)(UI_t::menucallbackinfo_t&, char**);//don't use this!!!
//	typedef MenuItemCallback mci_t;
	class MenuItem{ //menu type
	public:
		MenuItem(const __FlashStringHelper*, UIcallback*);//constructor
		const __FlashStringHelper* Label;
		char* Info;
		UIcallback *cb;//pointer to module in question

		int target;//id of list to link to
		bool link;//is this a link?
	};
	struct Menu {//type for menu
		//Menu() : list() {}//init the list in the constructor
		std::list<MenuItem> list;//the list containing MenuItems
		int parent; //parent id
		int id;
	};
	class UI : public Spin::Task {
	public:
		//Constructor
		//UI(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
		UI(int);
		~UI();
		void task();//start this as a task

		//Menu insertion & manipulation
//		UI& PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info);
		UI& PushItem(const __FlashStringHelper* Label);
		UI& PushItem(const __FlashStringHelper* Label, UIcallback*);//use this form for callback's that draw in the menu;
//		UI& PushItem(const __FlashStringHelper* Label, const __FlashStringHelper* Info, MenuItemCallback);

		//name = name of menu
		UI& SetParent(int name); //both take multi character literals, e.g., 'abc'
		UI& LinkTo(int name);
		UI& PushMenu(int name);//create new menu

		//screen
		void InitLCD(uint8_t X, uint8_t Y);//Must be called before task is started!
		void UpdateScreen();

		LiquidCrystal_I2C lcd;

		//pub vars
		bool beepOnChange;
	private:

		uint8_t sizeX, sizeY;
		Timer dispRefreshTimer;
		std::list<Menu> menus;//list of menus
		std::list<MenuItem>::iterator menuIt;//menu iterator
		uint8_t cursorOffset; //offset of the selected menu item from top of screen
		btndir_t button; //current button state
		btndir_t lastButton;
		std::list<Menu>::iterator currentMenu; //iterator pointing to the current menu
		unsigned long buttonScrollTimer;
		bool updateScreen; //true if screen needs update


		//methods
		void CheckButtons(std::list<MenuItem> &menu, std::list<MenuItem>::iterator &menuit);
		void DrawDisplay(std::list<MenuItem>::iterator);
		void JumpToMenu(std::list<Menu>::iterator);

		//helpers
		bool CheckItem(); //check that menu iterator is OK

	};
}
#endif
