#include"PidAllocator.h"
#include"ProcessError.h"
#include"ProcessResult.h"
#include <iostream>
#include <bitset>
#include <vector>
#include<mutex>
using namespace std;

PidAllocator* PidAllocator::getInstance() {
    static PidAllocator instance;
    return &instance;
}

int PidAllocator::allocatePid() {
    lock_guard<mutex> lock(mtx);
    /*找到第一个未分配的PID*/ 
    for (int i = nextPid; i < MAX_PID; ++i) {
        if (!PidBitmap[i]) {
            PidBitmap[i] = true;
            nextPid = i + 1;
            return i + 1;
        }
    }
    throw ProcessError("No Available Pids"); /*如果没有可用的PID，抛出异常*/ 
}

bool PidAllocator::validateAvailablePid(int pid) {
    if (pid > 0 && pid <= MAX_PID&&!PidBitmap[pid - 1]) return true;
    else return false;
}

bool PidAllocator::lockPid(int pid) {
    lock_guard<mutex> lock(mtx);
    if (pid > 0 && pid <= MAX_PID) {
        PidBitmap[pid - 1] = true;
        return true;
    }
    else {
        return false;
    }
}

bool PidAllocator::releasePid(int pid) {
    lock_guard<mutex> lock(mtx);
    if (pid > 0 && pid <= MAX_PID) {
        PidBitmap[pid - 1] = false; 
        return true;
    }
    else {
        return false;
    }
}

void PidAllocator::swapPid(int pid1, int pid2) {
    lock_guard<mutex> lock(mtx);
    bool temp = PidBitmap[pid1 - 1];
    PidBitmap[pid1 - 1] = PidBitmap[pid2 - 1];
    PidBitmap[pid2 - 1] = temp;
}

void PidAllocator::destroyAllocator() {
    delete this;
}

PidAllocator::~PidAllocator() {}