#include "lockorunlockpage.h"
#include "ui_lockorunlockpage.h"
#include "OS.h"
#include <QRegularExpressionValidator>

LockOrUnlockPage::LockOrUnlockPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LockOrUnlockPage)
{
    ui->setupUi(this);
    ui->LockEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
}

LockOrUnlockPage::~LockOrUnlockPage()
{
    delete ui;
}

void LockOrUnlockPage::on_QuitLockButton_clicked()
{
    this->hide();
}

void LockOrUnlockPage::on_LockButton_clicked()
{
    bool result = OS::getInstance()->blockProcess(ui->LockEdit->text().toInt());
    if(result){
        lock_successfully.show();
        this->hide();
    }
    else{
        lock_failed.show();
    }
}

void LockOrUnlockPage::on_UnlockButton_clicked()
{
    bool result = OS::getInstance()->unblockProcess(ui->LockEdit->text().toInt());
    if(result){
        lock_successfully.show();
        this->hide();
    }
    else{
        lock_failed.show();
    }
}
