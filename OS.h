#pragma once
#include"PCB.h"
#include<queue>

using namespace std;

class OS {
public:
	/*OS���Ϊ����ģʽ��ʹ��getInstance��������ȡʵ��*/
	static OS* getInstance();
	/*������������*/
	void readyProcessQueueSortByPriority();
	/*ÿ��ʱ��Ƭ������ȵĲ���*/
	void tickProcessScheduler();
	/*�ܳ�����Ȳ���*/
	void ProcessScheduler();

	/*һ��get����*/
    queue<PCB> getReadyProcessQueue();
    queue<PCB> getRunningProcessQueue();
    queue<PCB> getBlockedProcessQueue();
    queue<PCB> getAddProcessQueue();
	queue<PCB> getProcessControlBlockStorage();

    /*���ӳ����߼����ǰ��������ӵĳ������һ��������������У�����һ��ʱ��Ƭ�ٴ���*/
    void addProcess(PCB& pcb);
	/*����/��������߼����ǰ����г�����������������*/
    bool blockProcess(int pid);
	/*��ҳ��򣬽��������·�������������*/
    bool unblockProcess(int pid);
	/*�������ȼ��ĳ���ȽϷ��������ھ�����������*/
	bool compareProcessByPriority(PCB pcb1,PCB pcb2);

	/*һ���ӡ���������ڲ���*/
	void printReadyProcessQueue();
	void printAddProcessQueue();
	void printRunningProcessQueue();

private:
	/*����Ϳ���������Ϊ˽�У�����ģʽ*/
	OS();
	OS(const OS&) = default;
	OS& operator=(const OS&) = default;
	~OS();
	/*������У��ֱ��ʾ����������С����г�����С�����������о���������к��ܳ���洢����*/
	queue<PCB> ReadyProcessQueue;
	queue<PCB> RunningProcessQueue;
	queue<PCB> BlockedProcessQueue;
	queue<PCB> AddProcessQueue;
	queue<PCB> ProcessControlBlockStorage;
	/*������е���*/
	static const int MAX_RUNNING_PROCESS = 4;
	/*ģ��ʱ��Ƭ���*/
	static const int TICK_TIME_HUNDRED_MINISECONDS = 500;
	/*������־*/
	bool ReadyProcessQueueUpdateFlag;
};
