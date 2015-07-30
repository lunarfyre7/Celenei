#ifndef GUARD_timer
#define GUARD_timer


class Timer {
public:
	Timer();
	Timer SetInterval(unsigned long);//set the interval for the timer length
	Timer Reset();//resets the timer
	bool CheckInterval();//checks the interval set by SetInterval
	bool Check(unsigned long); //checks to see given time has elapses 
	bool Every(unsigned long);
	bool StaticCheck(unsigned long time);//checks if time has elapsed since last reset
	bool First(); //is this the first check? It returns true only once.
private:
	//FunctionPointer function;
	unsigned long lastTime;
	unsigned long interval;
	bool first;
};

#endif