#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lockorunlockpage.h"
#include "addprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshTable();

private slots:
    void on_ExitButton_clicked();

    void on_RefreshButton_clicked();

    void on_AddProcess_clicked();

    void on_UnblockProcess_clicked();

    void on_AddProcess2_clicked();

private:
    Ui::MainWindow *ui;

    LockOrUnlockPage lock_or_unlock_page;
    addprocess add_process;
};
#endif // MAINWINDOW_H
