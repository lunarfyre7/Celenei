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
#define LCD_I2C_ADDR 0x27 //address for I2C lcd module

#define LCD_X 16//screen width
#define LCD_Y 2 //screen height
#define LCD_REFRESH_TIME 100 //millis between screen refreshes


//+++++++++++++++++++++++++++
//Controls
//+++++++++++++++++++++++++++
//button types
//#define RESISTOR_BUTTON_MULTIPLEX //each button is multiplexed with resistors to one analog pin
#define DIRECT_5WAY_BUTTONS //each button has it's own pin

//button config
//#define BUTTON_PIN A0 //for multiplex
//pins for direct
#define BUTTON_PIN_U 2 //pin for the up button
#define BUTTON_PIN_D 4 //pin for the down button
#define BUTTON_PIN_L 5 //left
#define BUTTON_PIN_R 3 //right
#define BUTTON_PIN_C 6 //center

//#define BUTTONCHECK_TIME 10 //not used
//#define SCROLL_THRESHHOLD 750 //not used
//#define SCROLL_STEP 200 //not used


//+++++++++++++++++++++++++++
//SOUND
//+++++++++++++++++++++++++++
#define SPEAKER_PIN 9

//+++++++++++++++++++++++++++
//Other
//+++++++++++++++++++++++++++
//#define SEED 123 //seed for hashing. (Not used)


#endif
