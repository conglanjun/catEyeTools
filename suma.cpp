#include "suma.h"

QString Suma::baseUrl = "http://api.eobzz.com/httpApi.do?action=";
QString Suma::loginUrl = baseUrl + "loginIn&";
QString Suma::getUserInfos = baseUrl + "getUserInfos&";
QString Suma::getMobilenum = baseUrl + "getMobilenum&";
QString Suma::getVcodeAndHoldMobilenum = baseUrl + "getVcodeAndHoldMobilenum&";

Suma::Suma(CatEye *cat): catEye(cat)
{
    user = new UserInfo();
    pHttpFun = new HttpFun(this);
//        baseUrl = "http://api.eobzz.com/httpApi.do?action=";
//        loginUrl = baseUrl + "loginIn&";
//        getUserInfos = baseUrl + "getUserInfos&";
//        getMobilenum = baseUrl + "getMobilenum&";
//        getVcodeAndHoldMobilenum = baseUrl + "getVcodeAndHoldMobilenum&";
    connect(pHttpFun,SIGNAL(signal_requestFinished(bool,const QString&)), //http请求结束信号 login
            this,SLOT(slot_loginFinished(bool,const QString&)));
    connect(pHttpFun,SIGNAL(signal_userInfosFinished(bool,const QString&)), //http请求结束信号 getUserInfos
            this,SLOT(slot_getUserInfosFinished(bool,const QString&)));
}

// login
void Suma::slot_sumaLoginClicked()
{
    QString url = Suma::loginUrl + "uid=" + user->uid + "&pwd=" + user->pwd;
    pHttpFun->sendRequest(url);
}
// login 结束调用接口
void Suma::slot_loginFinished(bool flag,const QString& result)
{
    if(flag)
    {
        QStringList sections = result.split("|");
        user->token = sections.at(1).trimmed();
        catEye->textEdit->setText(user->uid + " " + user->pwd + " " + user->token);
    }
}

// 获取用户信息
void Suma:: slot_sumaUserInfosClicked()
{
    QString url = Suma::getUserInfos + "uid=" + user->uid + "&token=" + user->token;
    pHttpFun->sendRequest(url);
}

// 获取用户信息结束接口
void Suma::slot_getUserInfosFinished(bool flag, const QString& result)
{
    if(flag)
    {
        catEye->textEdit->setText(result);
    }
}

// 获取手机号
void Suma::slot_sumaGetMobilenumClicked()
{
    // pid=%s&uid=%s&token=%s&mobile=&size=%s  猫眼电影
    QString url = Suma::getMobilenum + "pid=10213" + "&uid=" + user->uid + "&token=" + user->token + "&size=" + 1;
    pHttpFun->sendRequest(url);
}

// 获取手机号结束接口
void Suma::slot_getMobilenumFinished(bool flag, const QString& result)
{
    if(flag)
    {
        catEye->textEdit->setText(result);
    }
}

void Suma::slot_httpsClicked()
{
//    pHttpFun->sendHttpsRequest("https://passport.meituan.com/account/captcha?rnd=0.027878410432939482");// 验证码图片
//    pHttpFun->sendPhoneValidateCode("http://passport.meituan.com/account/mobilesignupcode");// 手机验证码
    pHttpFun->sendSignup("http://passport.meituan.com/account/unitivesignup");//注册
}

void Suma::showValidateImage(QByteArray *byteArray)
{
    QPixmap pix;
    pix.loadFromData(*byteArray, "JPG");
    catEye->showImageLabel->setPixmap(pix.scaled(pix.size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

void Suma::showMessage(QString &str)
{
    QMessageBox::information(this->catEye, tr("Information"), str);
}



