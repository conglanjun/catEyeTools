#include "cateye.h"
#include "ui_cateye.h"

CatEye::CatEye(QWidget *parent)
    : QDialog(parent)
{
//    ui->setupUi(this);
    suma = new Suma(this);
    mainLayout = new QGridLayout(this);

    labelUrl = new QLabel(this);
    labelUrl->setText("输入地址");
    lineUrl = new QLineEdit(this);

    button = new QPushButton(this);
    button->setText("请求按钮");

    labelReply = new QLabel("Http返回");

    textEdit = new QTextEdit(this);

    sumaButton = new QPushButton(this);
    sumaButton->setText("速码账号");

    sumaUserInfosButton = new QPushButton(this);
    sumaUserInfosButton->setText("速码账号信息");

    sumaGetMobileButton = new QPushButton(this);
    sumaGetMobileButton->setText("速码获取手机号");

    httpsButton = new QPushButton(this);
    httpsButton->setText("https");

    showImageLabel = new QLabel(this);

    mainLayout->addWidget(labelUrl, 0, 0);
    mainLayout->addWidget(lineUrl, 0, 1);
    mainLayout->addWidget(button, 0, 2);
    mainLayout->addWidget(labelReply, 1, 0);
    mainLayout->addWidget(textEdit, 1, 1);
    mainLayout->addWidget(sumaButton, 2, 0);
    mainLayout->addWidget(sumaUserInfosButton, 3, 0);
    mainLayout->addWidget(httpsButton, 4, 0);
    mainLayout->addWidget(sumaGetMobileButton, 5, 0);
    mainLayout->addWidget(showImageLabel, 6, 0);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(slot_requestBtnClicked()));
    connect(sumaButton, SIGNAL(clicked(bool)), suma, SLOT(slot_sumaLoginClicked()));
    connect(sumaUserInfosButton, SIGNAL(clicked(bool)), suma, SLOT(slot_sumaUserInfosClicked()));
    connect(sumaGetMobileButton, SIGNAL(clicked(bool)), suma, SLOT(slot_sumaGetMobilenumClicked()));
    connect(httpsButton, SIGNAL(clicked(bool)), suma, SLOT(slot_httpsClicked()));
}

CatEye::~CatEye()
{
//    delete ui;
}

//请求按钮点击
void CatEye::slot_requestBtnClicked()
{
    HttpFun* pHttpFun = new HttpFun();
//    QMessageBox::information(this, tr("Information"), "！！！");
    QString strUrl = lineUrl->text().trimmed();
    connect(pHttpFun,SIGNAL(signal_requestFinished(bool,const QString&)), //http请求结束信号
            this,SLOT(slot_requestFinished(bool,const QString&)));
    pHttpFun->sendRequest(strUrl);
}

//请求结束
void CatEye::slot_requestFinished(bool bSuccess, const QString &strResult)
{
    if(bSuccess)
    {
        textEdit->setPlainText(strResult); //纯文本显示
    }
    else
    {
        textEdit->setPlainText(tr("请求失败！"));
    }

}
