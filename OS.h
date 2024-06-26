#pragma once
#include"PCB.h"
#include<queue>

using namespace std;

class OS {
public:
	/*OS设计为单例模式，使用getInstance函数来获取实例*/
	static OS* getInstance();
	/*就绪程序排序*/
	void readyProcessQueueSortByPriority();
	/*每个时间片程序调度的操作*/
	void tickProcessScheduler();
	/*总程序调度操作*/
	void ProcessScheduler();

	/*一般get方法*/
    queue<PCB> getReadyProcessQueue();
    queue<PCB> getRunningProcessQueue();
    queue<PCB> getBlockedProcessQueue();
    queue<PCB> getAddProcessQueue();
	queue<PCB> getProcessControlBlockStorage();

    /*增加程序，逻辑上是把所有增加的程序放入一个就绪缓冲队列中，到下一个时间片再处理*/
    void addProcess(PCB& pcb);
	/*阻塞/挂起程序，逻辑上是把所有程序放入挂起阻塞队列*/
    bool blockProcess(int pid);
	/*解挂程序，将程序重新放入就绪缓冲队列*/
    bool unblockProcess(int pid);
	/*基于优先级的程序比较方法，用于就绪程序排序*/
	bool compareProcessByPriority(PCB pcb1,PCB pcb2);

	/*一般打印方法，用于测试*/
	void printReadyProcessQueue();
	void printAddProcessQueue();
	void printRunningProcessQueue();

private:
	/*构造和拷贝方法均为私有，单例模式*/
	OS();
	OS(const OS&) = default;
	OS& operator=(const OS&) = default;
	~OS();
	/*五个队列，分别表示就绪程序队列、运行程序队列、阻塞程序队列就绪缓冲队列和总程序存储队列*/
	queue<PCB> ReadyProcessQueue;
	queue<PCB> RunningProcessQueue;
	queue<PCB> BlockedProcessQueue;
	queue<PCB> AddProcessQueue;
	queue<PCB> ProcessControlBlockStorage;
	/*最大运行道数*/
	static const int MAX_RUNNING_PROCESS = 4;
	/*模拟时间片间隔*/
	static const int TICK_TIME_HUNDRED_MINISECONDS = 500;
	/*辅助标志*/
	bool ReadyProcessQueueUpdateFlag;
};
