#include "module_test.h"
#include "../timer.h"
#include <MemoryFree.h>
#include <stdio.h>
#include "../utilfn.h"
using namespace UI_t;
extern UI ui;
typedef menucallbackinfo_t mci;

void RamCallback(mci &info, char** text) {
	int ram;
	static Timer timer;
	static bool init = true;
	if (init) {
		init = false;
		*text = (char*)calloc(9, sizeof(char));//plenty of space
	}
	if(timer.Every(1000))
	{
		ram = freeMemory();
		sprintf(*text, ": %db", freeMemory());
		ui.UpdateScreen();
	}
}
void DummyCB(mci &info, char** text) {//TODO create an init mechanism for these callbacks. Warning written like this the system crashes with one being called many times.
	static Timer timer;
	static bool init = true;
	if (init) {
		init = false;
		*text = (char*)calloc(9, sizeof(char));//plenty of space
	}
	if(timer.Every(586))
		{
			sprintf(*text, " %d %d", millis()%999, info.menuindex);
			ui.UpdateScreen();
		}
}
void DummyCB2(mci &info, char** text) {
	static Timer timer;
	static bool init = true;
	if (init) {
		init = false;
		*text = (char*)malloc(sizeof(char)*9);//plenty of space
	}
	if(timer.Check(1000))
		{
			sprintf(*text, " %d", millis()%999);
			ui.UpdateScreen();
		}
}

