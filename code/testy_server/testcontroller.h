#ifndef TESTCONTROLLER
#define TESTCONTROLLER

#include "server/Controller.h"
#include "server/Data.h"
#include <QtTest/QtTest>
#include <server/loader.h>
#include"shared/Utils/Direction.h"

class TestController: public QObject
{
    Q_OBJECT
    //void init(Data & data, Controller & contr, Loader &mapa);
private slots:
    void test_howMuchHurt_data();
    void test_howMuchHurt();

    void test_conflictPlayers_data();
    void test_conflictPlayers();


};

#endif // TESTCONTROLLER

