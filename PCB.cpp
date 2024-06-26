#include<string>
#include<iostream>
#include <ctime>
#include<cstdlib>
#include"PCB.h"
#include"PidAllocator.h"
#include"ProcessError.h"
#include"ProcessResult.h"
using namespace std;

PCB::PCB() {
	try {
		Pid = PidAllocator::getInstance()->allocatePid();
	}
	catch (const ProcessError& error) {
		std::cerr << "Error: " << error.what() << std::endl;
		return;
	}
    ProcessName = "casualProcess" + to_string(Pid);
	RequiredTimeSlice = rand() % 10 + 1;
	Priority = rand() % (MAX_PID+1);
	State = Init;
	NextProcess = nullptr;
}

PCB::PCB(string name, int pid, int required_time_slice, int priority, ProcessState state) {
	ProcessName = name;
	if (PidAllocator::getInstance()->validateAvailablePid(pid)) {
		Pid = pid;
		PidAllocator::getInstance()->lockPid(pid);
	}
	else {
		try {
			Pid = PidAllocator::getInstance()->allocatePid();
		}
		catch (const ProcessError& error) {
			std::cerr << "Error: " << error.what() << std::endl;
			return;
		}
	}
	if (required_time_slice <= 0) RequiredTimeSlice = rand() % 10 + 1;
	else RequiredTimeSlice = required_time_slice;
	Priority = priority;
	State = state;
	NextProcess = nullptr;
}

void PCB::destroyPCB() {
	PidAllocator::getInstance()->releasePid(this->Pid);
	this->NextProcess = nullptr;
}

string PCB::getProcessName() const{return ProcessName;}

int PCB::getPid() const { return Pid;}

int PCB::getRequiredTimeSlice() const { return RequiredTimeSlice; }

int PCB::getPriority() const { return Priority; }

ProcessState PCB::getState() const { return State; }

PCB* PCB::getNextProcess() const { return NextProcess; }

void PCB::tickReducePriority() {
	if (this->Pid == MAX_PID)
		return;
	else setPriority(Priority + 1);
}

bool PCB::setProcessName(const string& name) {
	if (name.empty()) {
		return false;
	}
	this->ProcessName = name;
	return true;
}

bool PCB::setPid(int pid) {
	if (pid > 0 && pid <= MAX_PID && PidAllocator::getInstance()->validateAvailablePid(pid)) PidAllocator::getInstance()->swapPid(this->Pid, pid);
	else return false;
	return true;
}

bool PCB::setRequiredTimeSlice(int required_time_slice) {
	if (required_time_slice >= 0) this->RequiredTimeSlice = required_time_slice;
	else return false;
	return true;
}

bool PCB::setPriority(int priority) {
	if (priority >= 0 && priority <= 255) this->Priority = priority;
	else return false;
	return true;
}

bool PCB::setState(ProcessState state) {
	this->State = state;
	return true;
}

bool PCB::setNextProcess(PCB* next_process) {
	this->NextProcess = next_process;
	return true;
}

void PCB::switchToBlockedState() {
	this->setState(ProcessState::Blocked);
}

void PCB::switchToReadyState() {
	this->setState(ProcessState::Ready);
}

void PCB::switchToRunningState() {
	this->setState(ProcessState::Running);
}


void PCB::switchToTerminateState() {
	this->setState(ProcessState::Terminate);
	this->destroyPCB();
}

void PCB::testPrint() {
	cout << "Process " << ProcessName
		<< " Priority: " << Priority
		<< " RequiredTimeSlice: " << RequiredTimeSlice
		<< " Pid: " << Pid
		<< " State: " << State << std::endl;
}
