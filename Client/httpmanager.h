#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>


class HttpManager : public QObject, public Singleton<HttpManager>, public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT
public:
    ~HttpManager();
private:
    friend class Singleton<HttpManager>;    // 基类需要创建子类的智能指针, 需要调用构造函数.
    HttpManager();
    QNetworkAccessManager m_manager;

    /**
     * @brief PostHttpReq 发送http请求
     * @param url 请求路径/路由
     * @param json 携带的数据
     * @param reqId 请求id
     * @param mod 哪个模块
     */
    void PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod);

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    // 当一个http发送完后发送信号
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
