#ifndef TESTCONTROLLER
#define TESTCONTROLLER

#include "server/Controller.h"
#include "server/Data.h"
#include <QtTest/QtTest>

class TestController: public QObject
{
    Q_OBJECT
private slots:
    void numberTwo();
    void numberOneJeden();
    void test_howMuchHurt_data();
    void test_howMuchHurt();


};

#endif // TESTCONTROLLER

