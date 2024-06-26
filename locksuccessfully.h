#ifndef LOCKSUCCESSFULLY_H
#define LOCKSUCCESSFULLY_H

#include <QDialog>

namespace Ui {
class LockSuccessfully;
}

class LockSuccessfully : public QDialog
{
    Q_OBJECT

public:
    explicit LockSuccessfully(QWidget *parent = nullptr);
    ~LockSuccessfully();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LockSuccessfully *ui;
};

#endif // LOCKSUCCESSFULLY_H
