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
    void test_isConflictPlayers_data();
    void test_isConflictPlayers();


};

#endif // TESTCONTROLLER

