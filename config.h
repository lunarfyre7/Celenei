#ifndef GUARD_cfg
#define GUARD_cfg

#include "Arduino.h"
#include "utilfn.h"

//+++++++++++++++++++++++++++
//General/Misc.
//+++++++++++++++++++++++++++

//+++++++++++++++++++++++++++
//Module enable/disable
//+++++++++++++++++++++++++++
#define EN_TEST_MODULE
// #define EN_GROW_CORE

//+++++++++++++++++++++++++++
//SCREEN
//+++++++++++++++++++++++++++
//#define LCD_PINS 11, 10, 5, 4, 3, 2
//#define LCD_PINS 7, 6, 5, 4, 3, 2
#define LCD_I2C_ADDR 0x27

#define LCD_16X2 //Doesn't do anything ATM; Only 2 row LCDs are supported currently
#define LCD_REFRESH_TIME 60 //millis between screen refreshes


//+++++++++++++++++++++++++++
//Controls
//+++++++++++++++++++++++++++
#define RESISTOR_BUTTON_MULTIPLEX
#define BUTTON_PIN A0
#define BUTTONCHECK_TIME 10
#define SCROLL_THRESHHOLD 750
#define SCROLL_STEP 200


//+++++++++++++++++++++++++++
//SOUND
//+++++++++++++++++++++++++++
#define SPEAKER_PIN 9

//+++++++++++++++++++++++++++
//Valves
//+++++++++++++++++++++++++++
	//TODO add abstraction for valves
#define VALVE_PIN_1 12
#define VALVE_PIN_2 11
#define VALVE_PIN_3 10


#endif
