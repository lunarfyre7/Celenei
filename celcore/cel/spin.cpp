#include "spin.h"

namespace Spin {
	static bool killCurrent = false; //true if current task is to be killed
	using namespace std;
	list<Spin::Task*> tasks;
	list<Spin::Task*>::iterator currentTask; //current iterator for running task

	void RegisterTask(Task* task) {//add task to tasklist
		//expand tasklist
		tasks.push_back(task);
	}
	void LoopTick() {//execute tasks in tasklist

		for (list<Spin::Task*>::iterator it=tasks.begin(); it != tasks.end(); ++it) {
			currentTask = it;
//			(**it)();
			(*it)->task();
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
