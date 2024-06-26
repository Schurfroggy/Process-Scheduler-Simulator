#include "locksuccessfully.h"
#include "ui_locksuccessfully.h"

LockSuccessfully::LockSuccessfully(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LockSuccessfully)
{
    ui->setupUi(this);
}

LockSuccessfully::~LockSuccessfully()
{
    delete ui;
}

void LockSuccessfully::on_buttonBox_accepted()
{
    this->hide();
}
