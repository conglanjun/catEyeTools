#ifndef HTTPFUN_H
#define HTTPFUN_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QFile>
#include <QBuffer>
#include <QCoreApplication>
#include <QDir>

class Suma;
#include "suma.h"

class HttpFun : public QObject
{
    Q_OBJECT
public:
    explicit HttpFun(Suma *suma = 0);
    void sendRequest(QString strUrl);// 根据url发起http请求
    void sendHttpsRequest(QString strUrl);
    void sendPhoneValidateCode(QString strUrl);
    void sendSignup(QString strUrl);
signals:
    void signal_requestFinished(bool bSuccess, const QString &strResult);// http请求结束
    void signal_userInfosFinished(bool bSuccess, const QString &strResult);// http请求结束
public slots:
    void slot_requestFinished();//http请求结束
    void slot_requestTimeout();//请求超时
    void slot_imagesOnFinished();// 验证码图片https请求结束
    void slot_phoneOnFinished();// 手机验证码http post请求结束
    void slot_signupOnFinished();// 注册http post请求结束

private:
    QNetworkAccessManager *m_pNetworkManager;// 网络管理类
    QNetworkReply *m_pNetworkReply;// 封装请求返回信息
    QTimer *m_pTimer;//请求超时计时器
public:
    static QString m_strUrl;//记录当前请求url
    Suma *m_suma;
};

#endif // HTTPFUN_H
