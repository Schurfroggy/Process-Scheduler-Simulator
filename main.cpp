#include "mainwindow.h"
#include "OS.h"
#include <QApplication>

void IntegTest() {
    //test
    PCB pcb1("testProcessA", 2, 5, 0, ProcessState::Ready);
    PCB pcb2("testProcessB", 3, 6, 3, ProcessState::Ready);
    PCB pcb3("testProcessC", 3, 6, 255, ProcessState::Ready);
    PCB pcb4("testProcessD", 5, 3, 15, ProcessState::Ready);
    PCB pcb5;
    PCB pcb6;
    PCB pcb7;
    pcb5.switchToReadyState();
    pcb6.switchToReadyState();
    pcb7.switchToReadyState();
    OS::getInstance()->addProcess(pcb1);
    OS::getInstance()->addProcess(pcb2);
    OS::getInstance()->addProcess(pcb3);
    OS::getInstance()->addProcess(pcb4);
    OS::getInstance()->addProcess(pcb5);
    OS::getInstance()->addProcess(pcb6);
    OS::getInstance()->addProcess(pcb7);
    //::getInstance()->ProcessScheduler();
}

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    QApplication a(argc, argv);
    IntegTest();
    OS::getInstance()->tickProcessScheduler();
    MainWindow w;
    w.show();
    return a.exec();
}

