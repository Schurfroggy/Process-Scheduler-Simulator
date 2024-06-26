#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OS.h"
#include<QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHeaderView* headerView = ui->tableWidget->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    refreshTable();
}

void MainWindow::refreshTable(){
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(40);
    queue<PCB> pcbBuffer;
    int cnt = 0;
    for(int i=0;i<3;i++){
        if(i==0) pcbBuffer = OS::getInstance()->getRunningProcessQueue();
        else if(i==1) pcbBuffer = OS::getInstance()->getReadyProcessQueue();
        else if(i==2) pcbBuffer = OS::getInstance()->getBlockedProcessQueue();
        while(!pcbBuffer.empty()){
            QTableWidgetItem *processName = new QTableWidgetItem(QString::fromStdString(pcbBuffer.front().getProcessName()));
            QTableWidgetItem *pid = new QTableWidgetItem(QString::number(pcbBuffer.front().getPid()));
            QTableWidgetItem *requiredTimeSlice = new QTableWidgetItem(QString::number(pcbBuffer.front().getRequiredTimeSlice()));
            QTableWidgetItem *priority =  new QTableWidgetItem(QString::number(pcbBuffer.front().getPriority()));
            QTableWidgetItem *state;
            switch(pcbBuffer.front().getState()){
                case ProcessState::Init:{
                    state = new QTableWidgetItem("初始化中");
                    break;
                }
                case ProcessState::Blocked:{
                    state = new QTableWidgetItem("已阻塞");
                    break;
                }
                case ProcessState::Ready: {
                    state = new QTableWidgetItem("就绪");
                    break;
                }
                case ProcessState::Running: {
                    state = new QTableWidgetItem("运行中");
                    break;
                }
                case ProcessState::Terminate: {
                    state = new QTableWidgetItem("终止");
                    break;
                }
            }
            processName->setTextAlignment(Qt::AlignCenter);
            pid->setTextAlignment(Qt::AlignCenter);
            requiredTimeSlice->setTextAlignment(Qt::AlignCenter);
            priority->setTextAlignment(Qt::AlignCenter);
            state->setTextAlignment(Qt::AlignCenter);
            if(i==0) state->setTextColor(QColor(76, 255, 0));
            if(i==2) state->setTextColor(QColor(255, 0, 4));

            ui->tableWidget->setItem(cnt,0,processName);
            ui->tableWidget->setItem(cnt,1,pid);
            ui->tableWidget->setItem(cnt,2,requiredTimeSlice);
            ui->tableWidget->setItem(cnt,3,priority);
            ui->tableWidget->setItem(cnt,4,state);
            pcbBuffer.pop();
            cnt++;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ExitButton_clicked()
{
    exit(0);
}

void MainWindow::on_RefreshButton_clicked()
{
    OS::getInstance()->tickProcessScheduler();
    refreshTable();
}

void MainWindow::on_AddProcess_clicked()
{
    PCB pcb;
    pcb.switchToReadyState();
    OS::getInstance()->addProcess(pcb);
}

void MainWindow::on_UnblockProcess_clicked()
{
    lock_or_unlock_page.show();
}

void MainWindow::on_AddProcess2_clicked()
{
    add_process.show();
}
