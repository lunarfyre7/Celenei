#ifndef GUARD_spin
#define GUARD_spin

#include "arduino.h"
#include "config.h"
#include <iterator> //TODO: replace <vector> with something with less sram usage.
#include <vector>

/*
Simplistic task scheduler system
*/

//typedef void(*TaskPtr)(const uint8_t&); 

namespace Spin {
	void RegisterTask(FunctionPointer); //Takes a function reference and adds it to the task list.
	//void RegisterTask(TaskPtr); //Takes a function reference and adds it to the task list. Callback function is passed it's index number;
	void LoopTick(); //Place this into the main loop.
	void KillTask();//kill current task. ONLY CALL FROM WITHIN THE TASK!!!
	void KillTask(const uint8_t&);//kill specified task
	// void OnlyOne(int id);//stops more than one copy on a task with the name id from running.
	// void OnlyOne(FunctionPointer);//stops more than one copy on a task from running.
	extern std::vector<FunctionPointer> tasks;
	extern uint8_t currentTask;
};

#endif