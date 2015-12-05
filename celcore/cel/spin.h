#ifndef GUARD_spin
#define GUARD_spin

#include "arduino.h"
#include "config.h"
#include <iterator> //TODO: replace <vector> with something with less sram usage.
#include <list> //TODO: use arrays instead of vectors

/*
Simplistic task scheduler system
*/

//typedef void(*TaskPtr)(const uint8_t&); 

namespace Spin {
	class Task {//task container
	public:
		virtual void task()=0;
		virtual ~Task() {};
	};
	void RegisterTask(Task*); //Takes a function reference and adds it to the task list.
	void LoopTick(); //Place this into the main loop.
	void KillTask();//kill current task. ONLY CALL FROM WITHIN THE TASK!!!
	void KillTask(const uint8_t&);//kill specified task
	extern std::list<Task*> tasks;
};

#endif
