#include "httpfun.h"
#include <QTextCodec>
#include "suma.h"

QString HttpFun::m_strUrl = "http://api.eobzz.com/httpApi.do?action=";
const int nHTTP_TIME = 10000;//10秒
HttpFun::HttpFun(Suma *suma) : m_suma(suma)
{
    m_pNetworkManager = new QNetworkAccessManager(this);
    m_pNetworkReply = NULL;
    m_pTimer = new QTimer;
//    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slot_requestTimeout()));// 超时信号
}

// 发起请求
void HttpFun::sendRequest(QString strUrl)
{
    m_strUrl = strUrl;
    QNetworkRequest netRquest;
    netRquest.setUrl(QUrl(strUrl)); //地址信息
//    connection.setRequestProperty("accept", "*/*");
//    connection.setRequestProperty("connection", "Keep-Alive");
//    connection.addRequestProperty("Content-Type", "text/html;charset=UTF-8");
//    connection.setRequestProperty("user-agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
    netRquest.setHeader(QNetworkRequest::ContentTypeHeader,"text/html;charset=utf-8");//设置ContentTypeHeader
    // 设定请求头
    netRquest.setRawHeader("user-agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1;SV1)");
    netRquest.setRawHeader("accept", "*/*");
    netRquest.setRawHeader("connection", "Keep-Alive");

    m_pNetworkReply = m_pNetworkManager->get(netRquest);
    connect(m_pNetworkReply,SIGNAL(finished()),this,SLOT(slot_requestFinished())); //请求完成信号
    m_pTimer->start(nHTTP_TIME);

}

//请求结束
void HttpFun::slot_requestFinished()
{
    m_pTimer->stop();//关闭定时器
    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        if(m_strUrl.startsWith(Suma::getLoginUrl()))
        {
            emit signal_requestFinished(true,strResult);//请求成功
        }else if(m_strUrl.startsWith(Suma::getGetUserInfos()))
        {
            emit signal_userInfosFinished(true, strResult);
        }
    }
    else
    {
        emit signal_requestFinished(false,strResult);//请求失败
    }
    m_pNetworkReply->deleteLater();
//    this->deleteLater(); //释放内存
}

//请求超时
void HttpFun::slot_requestTimeout()
{
    emit signal_requestFinished(false,"timeout");//请求失败
    m_pNetworkReply->deleteLater();
    this->deleteLater();//释放内存
}

//--------------------------美团注册---------------------------
void setRequestHeader(QNetworkRequest &request)
{
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("Host", "passport.meituan.com");
    request.setRawHeader("Referer", "http://passport.meituan.com/account/unitivesignup");
    request.setRawHeader("Origin", "http://passport.meituan.com");
    request.setRawHeader("Cookie", "uuid=d54d1e88ff1442cca202.1518068977.1.0.0; SERV=www; LREF=aHR0cDovL3d3dy5tZWl0dWFuLmNvbS9hY2NvdW50L3NldHRva2VuP2NvbnRpbnVlPWh0dHAlM0ElMkYlMkZ3d3cubWVpdHVhbi5jb20%3D; passport.sid=0xxOQw3xgRkfTQ0iJj4y7Iyoie39lGox; passport.sid.sig=vsFv5M1M0hSCS3u6PxHdxbiLAJA; __mta=150909193.1518068987291.1518168818956.1518168854945.3");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36");
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("X-Requested-With", "XMLHttpRequest");
    request.setRawHeader("X-Client", "javascript");
    request.setRawHeader("Accept-Encoding", "gzip, deflate");
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.9");
    request.setRawHeader("X-CSRF-Token", "IvK1oVzi-AdEvRYtyPGNFY7tezW99m7nxxIE");
}

// 获取验证码图片
void HttpFun::sendHttpsRequest(QString strUrl)
{
    QNetworkRequest request;
    QSslConfiguration config;

    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_0);
    request.setSslConfiguration(config);
    request.setUrl(QUrl(strUrl));
    setRequestHeader(request);
    m_pNetworkReply = m_pNetworkManager->get(request);

    connect(m_pNetworkReply , SIGNAL(finished()) , this , SLOT(slot_imagesOnFinished()));
}

void HttpFun::slot_imagesOnFinished()
{
    QByteArray byteArray = m_pNetworkReply->readAll();
//    QFile file("test.jpg");
//    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
//    {
//        file.write(byteArray);
//    }
//    file.flush();
//    file.close();
    m_suma->showValidateImage(&byteArray);
}

// 点击获取手机验证码
void HttpFun::sendPhoneValidateCode(QString strUrl)
{
    QNetworkRequest request;

    setRequestHeader(request);
    request.setUrl(QUrl(strUrl));
    setRequestHeader(request);
    QString strParam = "mobile=18740036034&captcha=rnn9";
    QByteArray byteArray = strParam.toUtf8();
    m_pNetworkReply = m_pNetworkManager->post(request, byteArray);

    connect(m_pNetworkReply , SIGNAL(finished()) , this , SLOT(slot_phoneOnFinished()));
}

void HttpFun::slot_phoneOnFinished()
{
    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        QString runPath = QDir::currentPath();
        m_suma->showMessage(runPath);
    }
}

// 注册
void HttpFun::sendSignup(QString strUrl)
{
    QNetworkRequest request;

    setRequestHeader(request);
    request.setUrl(QUrl(strUrl));
    setRequestHeader(request);
    QString strParam = "mobile=17068335574&captcha=&verifycode=647370&password=conglanjun111&password2=conglanjun111";
    QByteArray byteArray = strParam.toUtf8();
    m_pNetworkReply = m_pNetworkManager->post(request, byteArray);

    connect(m_pNetworkReply , SIGNAL(finished()) , this , SLOT(slot_phoneOnFinished()));
}

void HttpFun::slot_signupOnFinished()
{
    QByteArray resultContent = m_pNetworkReply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    if(nHttpCode == 200)//成功
    {
        QString runPath = QCoreApplication::applicationDirPath();
        m_suma->showMessage(runPath);
    }
}





