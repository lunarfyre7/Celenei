#ifndef GUARD_ui
#define GUARD_ui
#include "config.h"
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
//#include <lcdostream>
#include <iterator>
#include <list>
#include "timer.h"
#include "controls.h"
#include "sol/spin.h"
#include "../mod/base/modulebase.h"
class Module;//forward declaration
class UIcallback; //ditto

namespace sol {
//	namespace UI_t {
//		struct menucallbackinfo_t {
//			bool _new; //menu entry has just been selected
//			bool isSelected; //is the current menu item;
//			btndir_t button; //the button state
//			int  menuindex;
//		};
//	}

//	typedef void(*MenuItemCallback)(UI_t::menucallbackinfo_t&, char**);//TODO use lambdas instead of this
//	typedef void(Module::*MenuItemCallback)(UI_t::menucallbackinfo_t&, char**);//don't use this!!!
//	typedef MenuItemCallback mci_t;
	class MenuItem{ //menu type
	public:
		MenuItem(const __FlashStringHelper*, UIcallback*);//constructor
		~MenuItem();
		const __FlashStringHelper* Label;
		char* Info;
		UIcallback *cb;//pointer to module in question

		char target;//id of list to link to
		bool link;//is this a link?
	};
	struct Menu {//type for menu
		//Menu() : list() {}//init the list in the constructor
		std::list<MenuItem> list;//the list containing MenuItems
		int parent; //parent id
		char id;
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
		UI& SetParent(char name); //both take multi character literals, e.g., 'abc'
		UI& LinkTo(char name);
		UI& PushMenu(char name);//create new menu

		//deletion
		void EraseItem(const __FlashStringHelper* Label, char parent);
		void EraseMenu(char id);

		//screen
		void InitLCD(uint8_t X, uint8_t Y);//Must be called before task is started!
		void UpdateLine();//updates current line (use in callbacks)
		void UpdateScreen();//updates whole screen

		LiquidCrystal_I2C lcd;

		//pub vars
		bool beepOnChange;
		bool frozen;//true if ui is not to be drawn
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
		bool updateLine;
		bool dirty; //restart the whole drawing process


		//methods
		void CheckButtons(std::list<MenuItem> &menu, std::list<MenuItem>::iterator &menuit);
		void DrawDisplay(std::list<MenuItem>::iterator);
		void JumpToMenu(std::list<Menu>::iterator);
		Menu& FindMenuRef(char);//find a menu based on it's id;
		std::list<Menu>::iterator FindMenuIt(char);//find a menu iterator based on it's id;
		MenuItem& FindItem(const __FlashStringHelper *label, char parent);

		//helpers
		bool CheckItem(); //check that menu iterator is OK

		class Linker : public UIcallback {
			char id;
			UI &ui;
		public:
			Linker(UI &ui, char id);
			void callback(menucallbackinfo_t &);
		};
	};
}
extern sol::UI ui;
#endif
