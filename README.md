# Solaneae
Solaneae (solan-ee-I) is a modular open source firmware for Arduino. At present it is a general purpose framework with simple task scheduling and UI features.

**This readme is under construction. Solaneae is currently in an alpha state!**

# Building
Use the eclipse arduino plugin, follow the setup instructions, and finally clone the project into your workspace.
*only tested on an Arduino UNO*

# License 
Currently the license is GPL, this is subject to change however. By contributing to this repository you give me permission to change the license with or without permission.

# API/reference
## modulereg
Modulereg is a small class that runs initialization code in modules without needing to alter anything in the main source other than adding an `#include` in the module manifest file.
To register a callback with Modulereg create a new instance of MOdulereg passing the callback as the constructor parameter.
```
Module_reg regptr(mywrapper);
```

## UI
The UI class controls the menu system and is responsible for calling ui callbacks.

### pushing menu items

```
ui.PushItem(F("item1"), callback);
ui.PushItem(F("item2"), callback1);
ui.PushItem(F("item3"), callback2);
ui.PushItem(F(">menu1<")).LinkTo('m1');//create link to a submenu

//demo sub menu
	ui.PushItem(F(">Root<")).SetParent('m1').LinkTo(-1);//create link in submenu to the root menu, -1 links to root
	ui.PushItem(F("Child 1")).SetParent('m1');//note the SetParent and LinkTo chained method calling
	ui.PushItem(F("Child 2")).SetParent('m1');
	ui.PushItem(F("Child 3")).SetParent('m1');
```