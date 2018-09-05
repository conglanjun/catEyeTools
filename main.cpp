#include "cateye.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CatEye w;
    w.show();

    return a.exec();
}
