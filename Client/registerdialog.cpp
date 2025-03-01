#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmanager.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->passEdit->setEchoMode(QLineEdit::Password);
    ui->confirmEdit->setEchoMode(QLineEdit::Password);
    ui->errTip->setProperty("state", "normal");
    repolish(ui->errTip);
    connect(HttpManager::getInstance().get(), &HttpManager::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_getCode_clicked()
{
    auto email = ui->emailEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        // 发送http验证码
    } else {
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }
    // 解析Json字符串, res转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        showTip(tr("Json解析失败"), false);
        return;
    }
    // 解析错误, 解析出来不是对象
    if (!jsonDoc.isObject()) {
        showTip(tr("Json解析错误"), false);
        return;
    }
    // 解析为Json对象, 传递给回调函数处理
    m_handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    // 注册获取验证码回包的逻辑
    m_handlers.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱, 注意查收."), true);
        qDebug() << "Email is: " << email;
    });
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if (b_ok) ui->errTip->setProperty("state", "normal");
    else ui->errTip->setProperty("state", "err");
    ui->errTip->setText(str);
    repolish(ui->errTip);
}

