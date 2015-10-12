/*
 * controls.h
 *
 *  Created on: Oct 8, 2015
 *      Author: Jake Vandereay
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

enum btndir_t {
	up,
	down,
	left,
	right,
	center,
	none
};

#ifdef RESISTOR_BUTTON_MULTIPLEX
btndir_t DPad();
#endif


#endif /* CONTROLS_H_ */
