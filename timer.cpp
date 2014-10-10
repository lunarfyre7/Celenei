#include "timer.h"
#include "arduino.h" //used for millis(), should be replace with something else


Timer::Timer() {
	lastTime = millis();
	interval = 0;
}
Timer Timer::SetInterval(unsigned long interval) {
	this->interval = interval;
	return *this;
}
Timer Timer::Reset() {
	lastTime = millis();
	return *this;
}
bool Timer::CheckInterval() {
	return Check(interval);
}
bool Timer::Check(unsigned long time) {
	bool isGo = false;

	isGo = lastTime + time < millis();
	if (isGo) {
		lastTime = millis();
	}
	return isGo;
}
bool Timer::StaticCheck(unsigned long time) {
	return lastTime + time < millis();
}