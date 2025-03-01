#include "httpmanager.h"

HttpManager::~HttpManager()
{

}

HttpManager::HttpManager()
{
    connect(this, &HttpManager::sig_http_finish, this, &HttpManager::slot_http_finish);
}

void HttpManager::PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson(); // 转为 bytearray
    QNetworkRequest request(url);
    // 设置请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    // 构造伪闭包
    auto self = shared_from_this();

    QNetworkReply * reply = m_manager.post(request, data);  // post发送请求, 返回reply指针
    // 当完成时会发送信号
    connect(reply, &QNetworkReply::finished, [self, reply, reqId, mod](){
        // 处理错误情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            // 发送信号通知相关界面完成
            emit self->sig_http_finish(reqId, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        QString res = reply->readAll();
        // 发送信号通知完成
        emit self->sig_http_finish(reqId, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });

}

void HttpManager::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        // 通知注册模块
        emit sig_reg_mod_finish(id, res, err);

    }
}
