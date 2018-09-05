#ifndef SUMA_H
#define SUMA_H
#include <QString>
#include "userinfo.h"

class CatEye;

#include "cateye.h"

class HttpFun;
#include "httpfun.h"

class Suma : public QObject
{
    Q_OBJECT
public:
    Suma(CatEye *cat = 0);
public slots:
    void slot_sumaLoginClicked();
    void slot_sumaUserInfosClicked();
    void slot_sumaGetMobilenumClicked();
    void slot_httpsClicked();

    void slot_loginFinished(bool flag, const QString& result);
    void slot_getUserInfosFinished(bool flag, const QString& result);
    void slot_getMobilenumFinished(bool flag, const QString& result);

    void showValidateImage(QByteArray *byteArray);
    void showMessage(QString &str);


public:
    static QString getBaseUrl(){return baseUrl;}
    static QString getLoginUrl(){return loginUrl;}
    static QString getGetUserInfos(){return getUserInfos;}

public:
    static QString baseUrl;
    static QString loginUrl;
    static QString getUserInfos;
    static QString getMobilenum;
    static QString getVcodeAndHoldMobilenum;

    UserInfo *user;
    HttpFun* pHttpFun;

    CatEye *catEye;
};

#endif // SUMA_H
