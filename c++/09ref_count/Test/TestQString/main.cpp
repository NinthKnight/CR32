#include <QtCore/QCoreApplication>
#include <qstring.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str = "Hello World!";

    str =  QString("%1%2%3").arg("Hello").arg(1).arg("World!");


    return a.exec();
}
