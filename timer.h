#ifndef GUARD_timer
#define GUARD_timer


class Timer {
public:
	Timer();
	Timer SetInterval(unsigned long);//set the interval for the timer length
	Timer Reset();//resets the timer
	bool CheckInterval();//checks the interval set by SetInterval
	bool Check(unsigned long); //TODO: change name to Every()
	bool StaticCheck(unsigned long time);//checks if time has elapsed since last reset
private:
	//FunctionPointer function;
	unsigned long lastTime;
	unsigned long interval;
};

#endif