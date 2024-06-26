#include "lockfailed.h"
#include "ui_lockfailed.h"

lockfailed::lockfailed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lockfailed)
{
    ui->setupUi(this);
}

lockfailed::~lockfailed()
{
    delete ui;
}

void lockfailed::on_buttonBox_accepted()
{
    this->hide();
}
