#include "spin.h"

namespace Spin {
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
		}
	}
	void KillTask() {
//		tasks.erase(tasks.begin() + index);
		tasks.erase(currentTask);
	}
//	void KillTask() {
//		KillTask(currentTask);
//	}
	// void OnlyOne(int id) {

	// }
	// void OnlyOne(FunctionPointer fun) {

	// }
}
