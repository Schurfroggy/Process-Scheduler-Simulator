#pragma once
#include<string>
#include <ctime>
#include<cstdlib>
#include"ProcessResult.h"
using namespace std;

enum ProcessState {
	Init,
	Ready,
	Running,
    Blocked,
	Terminate
	/*五种进程状态，分别代表初始态，阻塞态，就绪态，运行态，终止态*/
};

class PCB {
public:
	PCB();
	PCB(string name, int pid, int required_time_slice, int priority, ProcessState state);
	void destroyPCB();

	/*一般get方法*/
	string getProcessName() const;
	int getPid() const;
	int getRequiredTimeSlice() const;
	int getPriority() const;
	ProcessState getState() const;
	PCB* getNextProcess() const;

	/*一般set方法*/
	bool setProcessName(const string& name);
	bool setPid(int pid);
	bool setRequiredTimeSlice(int required_time_slice);
	bool setPriority(int priority);
	bool setState(ProcessState state);
	bool setNextProcess(PCB* next_process);

	/*每次时间片的pcb操作*/
	void tickReducePriority();

	/*状态移动函数*/
	void switchToBlockedState();
	void switchToReadyState();
	void switchToRunningState();
	void switchToTerminateState();

	/*pcb打印方法，用于测试*/
	void testPrint();
private:
	/*几个重要参数，包括程序名，pid，所需时间，优先级，状态和指针（暂时未用到指针）*/
	string ProcessName;
	int Pid;
	int RequiredTimeSlice;
	int Priority;
	ProcessState State;
	PCB* NextProcess;
	/*0代表最小的优先级数字，但是是最大优先级（与linux同步）*/
	static const int MIN_PID = 0;
	static const int MAX_PID = 255;
};
