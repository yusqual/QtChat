#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include <QStyle>
#include <memory>
#include <iostream>
#include <mutex>
#include <QByteArray>
#include <QNetworkReply>

/**
 * @brief repolish 刷新qss
 */
extern std::function<void(QWidget*)> repolish;

// 请求id
enum ReqId {
    ID_GET_VERIFY_CODE = 1001,  // 获取验证码
    ID_REG_USER = 1002,         // 注册用户
};

// 模块
enum Modules {
    REGISTERMOD = 0,
};

// 错误码
enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1,   // Json解析失败
    ERR_NETWORK = 2, // 网络错误
};

#endif // GLOBAL_H
