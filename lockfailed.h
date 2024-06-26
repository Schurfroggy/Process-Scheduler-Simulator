#ifndef LOCKFAILED_H
#define LOCKFAILED_H

#include <QDialog>

namespace Ui {
class lockfailed;
}

class lockfailed : public QDialog
{
    Q_OBJECT

public:
    explicit lockfailed(QWidget *parent = nullptr);
    ~lockfailed();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::lockfailed *ui;
};

#endif // LOCKFAILED_H
