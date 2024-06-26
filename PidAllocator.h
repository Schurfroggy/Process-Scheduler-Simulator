#pragma once
#include <iostream>
#include <bitset>
#include <vector>
#include<mutex>
#include"ProcessResult.h"
using namespace std;

const int MAX_PID = 1000; 

class PidAllocator {
private:
    /*PidAllocator是pid分配类，也设计为单例模式防止多个实例时出错*/
    /*使用位图来代表pid分配情况*/
    bitset<MAX_PID> PidBitmap;
    int nextPid;
    /*mutex用于互斥锁*/
    mutex mtx;
    /*私有构造和拷贝函数，单例模式*/
    PidAllocator() { nextPid = 1; PidBitmap.reset(); } 
    PidAllocator(const PidAllocator&) = default;
    PidAllocator& operator=(const PidAllocator&) = default;
    ~PidAllocator();

public:
    /*获取实例*/
    static PidAllocator* getInstance();
    /*删除实例*/
    void destroyAllocator();
    /*核心功能，分配下一个可用pid*/
    int allocatePid();
    /*手动锁下pid*/
    bool lockPid(int pid);
    /*解锁pid*/
    bool releasePid(int pid);
    /*查询pid是否可用（是否在位图中为空）*/
    bool validateAvailablePid(int pid);
    /*交换pid*/
    void swapPid(int pid1, int pid2);
};