#ifndef GUARD_utilfn
#define GUARD_utilfn
#include "config.h"
#include <LiquidCrystal_I2C.h>


//small utility functions

typedef void(*FunctionPointer)(); 
void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal_I2C lcd);
void beep();
template <typename T>
void DebugP(T);

#endif
