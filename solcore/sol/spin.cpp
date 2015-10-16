#include "spin.h"

namespace Spin {
	static bool killCurrent = false; //true if current task is to be killed
	using namespace std;
	list<FunctionPointer> tasks;
	list<FunctionPointer>::iterator currentTask; //current iterator for running task

	void RegisterTask(FunctionPointer function) {//add task to tasklist
		//expand tasklist
		tasks.push_back(function);
	}
	void LoopTick() {//execute tasks in tasklist

		for (list<FunctionPointer>::iterator it=tasks.begin(); it != tasks.end(); ++it) {
			currentTask = it;
			(**it)();
			if (killCurrent) {
				tasks.erase(it++);
				killCurrent = false;
			}
		}
	}
	void KillTask() { //kills the task that calls it

		killCurrent = true;
	}
}
