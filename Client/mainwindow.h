/**********************************************************
 * @file         mainwindow.h
 * @brief        主窗口
 *
 * @author       yusqual
 * @date         2025/02/27
 * @history
 **********************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotSwitchReg();

private:
    Ui::MainWindow *ui;
    LoginDialog *m_loginDlg;
    RegisterDialog *m_regDlg;
};
#endif // MAINWINDOW_H
