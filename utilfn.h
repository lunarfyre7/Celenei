#ifndef GUARD_utilfn
#define GUARD_utilfn
#include "config.h"

//small utility functions

typedef void(*FunctionPointer)(); 

extern void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal lcd);

#endif