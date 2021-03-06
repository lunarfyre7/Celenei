/*
 * controls.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: Jake Vandereay
 */
#include <Arduino.h>
#include "config.h"
#include "controls.h"


#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir_t DPad() {
int reading = analogRead(BUTTON_PIN);
//  Serial.print(F("dpad val: ")); Serial.println(reading); //uncomment for recalibration info
  btndir_t val;
  					 val = up;
  if (reading < 730) val = left;
  if (reading < 655) val = center;
  if (reading < 440) val = down;
  if (reading < 265) val = right;
  if (reading < 100) val = none;
  return val;
}
#endif

#ifdef DIRECT_5WAY_BUTTONS
btndir_t DPad() {
	btndir_t val = none;
	if (!digitalRead(BUTTON_PIN_D)) val = down;
	if (!digitalRead(BUTTON_PIN_L)) val = left;
	if (!digitalRead(BUTTON_PIN_U)) val = up;
	if (!digitalRead(BUTTON_PIN_R)) val = right;
	if (!digitalRead(BUTTON_PIN_C)) val = center;
	return val;
}
#endif
