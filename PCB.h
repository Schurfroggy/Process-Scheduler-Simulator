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
	/*���ֽ���״̬���ֱ�����ʼ̬������̬������̬������̬����ֹ̬*/
};

class PCB {
public:
	PCB();
	PCB(string name, int pid, int required_time_slice, int priority, ProcessState state);
	void destroyPCB();

	/*һ��get����*/
	string getProcessName() const;
	int getPid() const;
	int getRequiredTimeSlice() const;
	int getPriority() const;
	ProcessState getState() const;
	PCB* getNextProcess() const;

	/*һ��set����*/
	bool setProcessName(const string& name);
	bool setPid(int pid);
	bool setRequiredTimeSlice(int required_time_slice);
	bool setPriority(int priority);
	bool setState(ProcessState state);
	bool setNextProcess(PCB* next_process);

	/*ÿ��ʱ��Ƭ��pcb����*/
	void tickReducePriority();

	/*״̬�ƶ�����*/
	void switchToBlockedState();
	void switchToReadyState();
	void switchToRunningState();
	void switchToTerminateState();

	/*pcb��ӡ���������ڲ���*/
	void testPrint();
private:
	/*������Ҫ������������������pid������ʱ�䣬���ȼ���״̬��ָ�루��ʱδ�õ�ָ�룩*/
	string ProcessName;
	int Pid;
	int RequiredTimeSlice;
	int Priority;
	ProcessState State;
	PCB* NextProcess;
	/*0������С�����ȼ����֣�������������ȼ�����linuxͬ����*/
	static const int MIN_PID = 0;
	static const int MAX_PID = 255;
};
