#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    // 注册按钮被点击后发出信号
    connect(ui->regBtn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
