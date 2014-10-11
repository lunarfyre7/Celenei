#ifndef GUARD_utilfn
#define GUARD_utilfn
#include <LiquidCrystal.h>

//small utility functions

typedef void(*FunctionPointer)(); 
void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal lcd);

#endif