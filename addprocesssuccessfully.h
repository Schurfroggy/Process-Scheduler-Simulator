#ifndef ADDPROCESSSUCCESSFULLY_H
#define ADDPROCESSSUCCESSFULLY_H

#include <QDialog>

namespace Ui {
class addprocesssuccessfully;
}

class addprocesssuccessfully : public QDialog
{
    Q_OBJECT

public:
    explicit addprocesssuccessfully(QWidget *parent = nullptr);
    ~addprocesssuccessfully();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addprocesssuccessfully *ui;
};

#endif // ADDPROCESSSUCCESSFULLY_H
