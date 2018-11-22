#include <QCoreApplication>

namespace CR32 {
    void foo(){

         printf("foo");
    }
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    CR32::foo();
    printf("Hello World!");

    return 0;
}
