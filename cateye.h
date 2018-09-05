#ifndef CATEYE_H
#define CATEYE_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "httpfun.h"

class Suma;

#include "suma.h"
namespace Ui {
class CatEye;
}

class CatEye : public QDialog
{
    Q_OBJECT

public:
    CatEye(QWidget *parent = 0);
    ~CatEye();
public slots:
    void slot_requestBtnClicked();
    void slot_requestFinished(bool,const QString&);

public:
    Ui::CatEye *ui;
    QLabel *labelUrl;
    QLineEdit *lineUrl;
    QPushButton *button;
    QLabel *labelReply;
    QTextEdit *textEdit;
    QGridLayout *mainLayout;

    QPushButton *sumaButton;
    QPushButton *sumaUserInfosButton;
    QPushButton *sumaGetMobileButton;
    QPushButton *httpsButton;
    QLabel *showImageLabel;
    Suma *suma;
};

#endif // CATEYE_H
