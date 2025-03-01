#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_loginDlg = new LoginDialog(this);
    setCentralWidget(m_loginDlg);   // 设置为核心组件
//    m_loginDlg->show();

    // 创建和注册消息链接
    connect(m_loginDlg, &LoginDialog::switchRegister, this,&MainWindow::slotSwitchReg);

    m_regDlg = new RegisterDialog(this);

    m_loginDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);  // 嵌入主窗口
    m_regDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    m_regDlg->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSwitchReg()
{
    setCentralWidget(m_regDlg);
    m_loginDlg->hide();
    m_regDlg->show();
}

