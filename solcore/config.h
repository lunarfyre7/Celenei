#ifndef GUARD_cfg
#define GUARD_cfg

#include "Arduino.h"
#include "sol/utilfn.h"

//+++++++++++++++++++++++++++
//Debug
//+++++++++++++++++++++++++++
//#define DEBUG_INFO

//+++++++++++++++++++++++++++
//SCREEN
//+++++++++++++++++++++++++++
//#define LCD_PINS 11, 10, 5, 4, 3, 2
//#define LCD_PINS 7, 6, 5, 4, 3, 2
#define LCD_I2C_ADDR 0x27

#define LCD_X 16
#define LCD_Y 2
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
//Other
//+++++++++++++++++++++++++++
#define SEED 123


#endif
