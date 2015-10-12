#ifndef GUARD_utilfn
#define GUARD_utilfn
#include "config.h"
#include <LiquidCrystal_I2C.h>

//macros
#define P(thing) Serial.print(thing) //print thing
#define PL(thing) Serial.println(thing) //print line
#define PF(string) Serial.print(F(string)) //print flash string
#define PLF(string) Serial.println(F(string)) //print flash string with newline
#define NL Serial.print("/n") //new line

//http://stackoverflow.com/a/17624752/826312
#define PP_CAT(a, b) PP_CAT_I(a, b)
#define PP_CAT_I(a, b) PP_CAT_II(~, a ## b)
#define PP_CAT_II(p, res) res

#define UNIQUE_NAME(base) PP_CAT(base, __LINE__)
//#define UN(base) UNIQUE_NAME(base)

//small utility functions

typedef void(*FunctionPointer)(); 
void ClearSection(uint8_t X, uint8_t Y, uint8_t len, LiquidCrystal_I2C lcd);
void beep();
template<typename T>
void DebugP(T in) {
#ifdef DEBUG_INFO
	Serial.print("[debug]");
	Serial.println(in);
	return;
#else
	return;
#endif
}

#endif //guard
