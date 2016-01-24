#include "server/serverwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWindow w;
    w.show();

    return a.exec();
}

/*
//testy jednostkowe
#include "testy_server/testcontroller.h"
QTEST_MAIN(TestController)
#include "moc_testcontroller.cpp"

*/
