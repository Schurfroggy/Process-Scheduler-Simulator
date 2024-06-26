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
    /*PidAllocator��pid�����࣬Ҳ���Ϊ����ģʽ��ֹ���ʵ��ʱ����*/
    /*ʹ��λͼ������pid�������*/
    bitset<MAX_PID> PidBitmap;
    int nextPid;
    /*mutex���ڻ�����*/
    mutex mtx;
    /*˽�й���Ϳ�������������ģʽ*/
    PidAllocator() { nextPid = 1; PidBitmap.reset(); } 
    PidAllocator(const PidAllocator&) = default;
    PidAllocator& operator=(const PidAllocator&) = default;
    ~PidAllocator();

public:
    /*��ȡʵ��*/
    static PidAllocator* getInstance();
    /*ɾ��ʵ��*/
    void destroyAllocator();
    /*���Ĺ��ܣ�������һ������pid*/
    int allocatePid();
    /*�ֶ�����pid*/
    bool lockPid(int pid);
    /*����pid*/
    bool releasePid(int pid);
    /*��ѯpid�Ƿ���ã��Ƿ���λͼ��Ϊ�գ�*/
    bool validateAvailablePid(int pid);
    /*����pid*/
    void swapPid(int pid1, int pid2);
};