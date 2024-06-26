#ifndef ADDPROCESS_H
#define ADDPROCESS_H

#include <QWidget>
#include "addprocesssuccessfully.h"

namespace Ui {
class addprocess;
}

class addprocess : public QWidget
{
    Q_OBJECT

public:
    explicit addprocess(QWidget *parent = nullptr);
    ~addprocess();

private slots:
    void on_quitButton_clicked();

    void on_addButton_clicked();

private:
    Ui::addprocess *ui;
    addprocesssuccessfully add_process_successfully;
};

#endif // ADDPROCESS_H
