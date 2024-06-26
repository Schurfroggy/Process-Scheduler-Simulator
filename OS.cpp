#include<iostream>
#include<vector>
#include<algorithm>
#include<Windows.h>
#include"OS.h"
using namespace std;

OS* OS::getInstance() {
	static OS instance;
	return &instance;
}

OS::OS() {
	ReadyProcessQueueUpdateFlag = false;
}
OS::~OS() {}

void OS::tickProcessScheduler() {/*����tick��һ��ʱ��Ƭ��ʱ����ϵͳ�Ĳ���*/
	/*1.���������еĳ�������Ȩ-1/Ҫ������ʱ��-1���������ʱ��Ϊ0�򵯳��������ڱ����������ȼ��ߵĳ������ȼ����ָ��ͣ�����ʵ������Ȩ+1*/
	if (!RunningProcessQueue.empty()) {
		RunningProcessQueue.front().tickReducePriority();
		RunningProcessQueue.front().setRequiredTimeSlice(RunningProcessQueue.front().getRequiredTimeSlice() - 1);

		if (RunningProcessQueue.front().getRequiredTimeSlice() == 0) {
			RunningProcessQueue.front().switchToTerminateState();
			RunningProcessQueue.pop();
		}
	}
	/*2.������е���������������Ԥ�����зǿգ���ѡ������Ԥ�����е�ͷ�����򣬼��������Ϳյ������*/
	if (RunningProcessQueue.size() < MAX_RUNNING_PROCESS && !ReadyProcessQueue.empty()) {
		int AddProcessAmount = 0;
		if (ReadyProcessQueue.size() >= MAX_RUNNING_PROCESS - RunningProcessQueue.size())
			AddProcessAmount = MAX_RUNNING_PROCESS - RunningProcessQueue.size();
		else AddProcessAmount = ReadyProcessQueue.size();

		while (AddProcessAmount != 0) {
			ReadyProcessQueue.front().switchToRunningState();
			RunningProcessQueue.push(move(ReadyProcessQueue.front()));
			ReadyProcessQueue.pop();
			AddProcessAmount -= 1;
		}
	}
	/*3.��Ԥ���������н��д������ճ���״̬���벻ͬ�����У����������Ԥ�����У������ø����ź�Ϊtrue*/
	while (!AddProcessQueue.empty()) {
		switch (AddProcessQueue.front().getState()) {
		    case ProcessState::Init:{
				//���ԣ�ֱ��pop
				break;
			}
			case ProcessState::Blocked:{
				BlockedProcessQueue.push(move(AddProcessQueue.front()));
				break;
			}
			case ProcessState::Ready: {
				ReadyProcessQueue.push(move(AddProcessQueue.front()));
				ReadyProcessQueueUpdateFlag = true;
				break;
			}
			case ProcessState::Running: {
				//bug�����ԣ�ֱ��pop
				break;
			}
			case ProcessState::Terminate: {
				//bug�����ԣ�ֱ��pop
				break;
			}
		}
		AddProcessQueue.pop();
	}
	/*4.���Ԥ�����и����ź�Ϊtrue������һ�����ȼ����򣬱������ȼ��ߵĳ������ȱ�����*/
	if (ReadyProcessQueueUpdateFlag == true) {
		readyProcessQueueSortByPriority();
		ReadyProcessQueueUpdateFlag = false;
	}
}

void OS::ProcessScheduler() {
    /*���������Զ���������ȵģ��ֱ�����*/
	while (true) {
		tickProcessScheduler();
		printAddProcessQueue();
		printReadyProcessQueue();
		printRunningProcessQueue();
		cout << endl;
		Sleep(this->TICK_TIME_HUNDRED_MINISECONDS);
		cout << "---------------------------------------" << endl;
	}
}

bool OS::compareProcessByPriority(PCB pcb1, PCB pcb2) {
	return pcb1.getPriority() < pcb2.getPriority();
}

void OS::readyProcessQueueSortByPriority() {
	/*ʹ��sort�����Ծ������н�������*/
	if (this->ReadyProcessQueue.empty())return;
	vector<PCB> Temp;
	while (!this->ReadyProcessQueue.empty()) {
		Temp.push_back(this->ReadyProcessQueue.front());
		this->ReadyProcessQueue.pop();
	}
	sort(Temp.begin(), Temp.end(), [this](const PCB& pcb1, const PCB& pcb2) {
		return this->compareProcessByPriority(pcb1, pcb2);
		});
	for (PCB pcb : Temp) {
		ReadyProcessQueue.push(pcb);
	}
}

queue<PCB> OS::getReadyProcessQueue() { return ReadyProcessQueue;}

queue<PCB> OS::getRunningProcessQueue() { return RunningProcessQueue;}

queue<PCB> OS::getBlockedProcessQueue() { return BlockedProcessQueue;}

queue<PCB> OS::getAddProcessQueue() { return AddProcessQueue;}

queue<PCB> OS::getProcessControlBlockStorage() { return ProcessControlBlockStorage; }

void OS::addProcess(PCB& pcb) {
	AddProcessQueue.push(pcb);
	ProcessControlBlockStorage.push(pcb);
}

bool OS::blockProcess(int pid) {
    vector<PCB> temp;
    PCB* pcb_ = nullptr;
    bool flag = false;
    while (!ReadyProcessQueue.empty()) {
        if (ReadyProcessQueue.front().getPid() == pid) {
            pcb_ = &ReadyProcessQueue.front();
            ReadyProcessQueue.pop();
            flag = true;
            continue;
        }
        temp.push_back(ReadyProcessQueue.front());
        ReadyProcessQueue.pop();
    }
    for (PCB p : temp) {
        ReadyProcessQueue.push(p);
    }
    if (flag) {
        pcb_->switchToBlockedState();
        addProcess(*pcb_);
        return true;
    }

    temp.clear();
    flag = false;
    pcb_ = nullptr;
    while (!RunningProcessQueue.empty()) {
        if (RunningProcessQueue.front().getPid() == pid) {
            pcb_ = &RunningProcessQueue.front();
            RunningProcessQueue.pop();
            flag = true;
            continue;
        }
        temp.push_back(RunningProcessQueue.front());
        RunningProcessQueue.pop();
    }
    for (PCB p : temp) {
        RunningProcessQueue.push(p);
    }
    if (flag) {
        pcb_->switchToBlockedState();
        addProcess(*pcb_);
        return true;
    }
    return false;
}

bool OS::unblockProcess(int pid) {
    vector<PCB> temp;
    PCB* pcb_ = nullptr;
    bool flag = false;
    while (!BlockedProcessQueue.empty()) {
        if (BlockedProcessQueue.front().getPid() == pid) {
            pcb_ = &BlockedProcessQueue.front();
            BlockedProcessQueue.pop();
            flag = true;
            continue;
        }
        temp.push_back(BlockedProcessQueue.front());
        BlockedProcessQueue.pop();
    }
    for (PCB p : temp) {
        BlockedProcessQueue.push(p);
    }
    if (flag) {
        pcb_->switchToReadyState();
        addProcess(*pcb_);
        return true;
    }
    else return false;
}


void OS::printReadyProcessQueue() {
	cout << "Ready Process Queue contains:" << std::endl;
	std::vector<PCB> vec;
	while (!ReadyProcessQueue.empty()) {
		vec.push_back(ReadyProcessQueue.front());
		ReadyProcessQueue.pop();
	}
	for (PCB pcb : vec) {
		pcb.testPrint();
	}
	for (PCB& pcb : vec) {
		ReadyProcessQueue.push(pcb);
	}
}

void OS::printAddProcessQueue() {
	cout << "Add Process Queue contains:" << std::endl;
	std::vector<PCB> vec;
	while (!AddProcessQueue.empty()) {
		vec.push_back(AddProcessQueue.front());
		AddProcessQueue.pop();
	}
	for (PCB pcb : vec) {
		pcb.testPrint();
	}
	for (PCB& pcb : vec) {
		AddProcessQueue.push(pcb);
	}
}

void OS::printRunningProcessQueue() {
	cout << "Running Process Queue contains:" << std::endl;
	std::vector<PCB> vec;
	while (!RunningProcessQueue.empty()) {
		vec.push_back(RunningProcessQueue.front());
		RunningProcessQueue.pop();
	}
	for (PCB pcb : vec) {
		pcb.testPrint();
	}
	for (PCB& pcb : vec) {
		RunningProcessQueue.push(pcb);
	}
}

