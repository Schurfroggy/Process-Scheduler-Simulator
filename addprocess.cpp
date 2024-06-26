#include "addprocess.h"
#include "ui_addprocess.h"
#include "OS.h"
#include <string>

addprocess::addprocess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addprocess)
{
    ui->setupUi(this);
    //ui->LockEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->pidEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->timeEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->priorityEdit->setValidator(new QRegExpValidator(QRegExp("^25[0-5]|2[0-4][0-9]|[01][0-9][0-9]$")));
    ui->stateBox->setEditable(false);
    ui->stateBox->setCurrentIndex(1);
}

addprocess::~addprocess()
{
    delete ui;
}

void addprocess::on_quitButton_clicked()
{
    this->hide();
}


void addprocess::on_addButton_clicked()
{
    std::string process_name = std::string(ui->processNameEdit->text().toLocal8Bit());
    int pid = ui->pidEdit->text().toInt();
    int required_time_slice = ui->timeEdit->text().toInt();
    int priority = ui->priorityEdit->text().toInt();
    int state = ui->stateBox->currentIndex();
    PCB pcb(process_name,pid,required_time_slice,priority,ProcessState(state));
    OS::getInstance()->addProcess(pcb);
    add_process_successfully.show();
    this->hide();
}
