#ifndef LOCKORUNLOCKPAGE_H
#define LOCKORUNLOCKPAGE_H

#include <QWidget>
#include "locksuccessfully.h"
#include "lockfailed.h"

namespace Ui {
class LockOrUnlockPage;
}

class LockOrUnlockPage : public QWidget
{
    Q_OBJECT

public:
    explicit LockOrUnlockPage(QWidget *parent = nullptr);
    ~LockOrUnlockPage();

private slots:
    void on_QuitLockButton_clicked();

    void on_LockButton_clicked();

    void on_UnlockButton_clicked();

private:
    Ui::LockOrUnlockPage *ui;
    LockSuccessfully lock_successfully;
    lockfailed lock_failed;
};

#endif // LOCKORUNLOCKPAGE_H
