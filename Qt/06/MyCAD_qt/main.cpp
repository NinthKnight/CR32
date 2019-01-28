#include "mainwindow.h"
#include <QApplication>
#include "line.h"
#include "rect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //注册元类型
    qRegisterMetaType<line>("line");
    qRegisterMetaType<Rect>("Rect");


    return a.exec();
}
