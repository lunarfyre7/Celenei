#include "spin.h"

namespace Spin {
	std::vector<FunctionPointer> tasks;
	uint8_t currentTask = 0;

	void RegisterTask(FunctionPointer function) {//add task to tasklist
		//expand tasklist
		tasks.push_back(function);
	}
	void LoopTick() {//execute tasks in tasklist
		uint8_t length = tasks.size();

		for (uint8_t i = 0; i < length; i++) {
			currentTask = i;
			(*tasks[i])();
		}
	}
	void KillTask(const uint8_t& index) {
		tasks.erase(tasks.begin() + index);
	}
	void KillTask() {
		KillTask(currentTask);
	}
	// void OnlyOne(int id) {

	// }
	// void OnlyOne(FunctionPointer fun) {

	// }
}
