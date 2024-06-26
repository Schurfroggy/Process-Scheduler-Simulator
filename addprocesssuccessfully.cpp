#include "addprocesssuccessfully.h"
#include "ui_addprocesssuccessfully.h"

addprocesssuccessfully::addprocesssuccessfully(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addprocesssuccessfully)
{
    ui->setupUi(this);
}

addprocesssuccessfully::~addprocesssuccessfully()
{
    delete ui;
}

void addprocesssuccessfully::on_buttonBox_accepted()
{
    this->hide();
}
