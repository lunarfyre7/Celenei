#ifndef GUARD_cfg
#define GUARD_cfg

#include "arduino.h"
#include <LiquidCrystal.h>
#include "utilfn.h"

//+++++++++++++++++++++++++++
//SCREEN / UI
//+++++++++++++++++++++++++++
#define LCD_16X2
#define LCD_REFRESH_TIME 60 //millis between screen refreshes


//controls
#define RESISTOR_BUTTON_MULTIPLEX
#define BUTTONPIN A0
#define BUTTONCHECK_TIME 10 
//+++++++++++++++++++++++++++
//SOUND 
//+++++++++++++++++++++++++++
#define SPEAKER_PIN 8


#endif