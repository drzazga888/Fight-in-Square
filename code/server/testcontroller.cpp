#include "testcontroller.h"
void TestController::numberTwo()
{
    Data dat=Data();
    Controller contr(dat);
    QPoint player3(0,0);
    QPoint player4(10,10);
    //QCOMPARE(contr.isConflictPlayers(player3,player4),false);
 /*   QString str="hello";
    QVERIFY(str.toUpper()=="HELLO");
*/}
void TestController::numberOneJeden()
{
    Data dat=Data();
    Controller contr(dat);
    QPoint player1(2,4);
    QPoint player2(4,6);
    QPoint player3(0,0);
    QPoint player4(10,10);
    //QCOMPARE(contr.isConflictPlayers(player1,player2),true);
    //QCOMPARE(contr.isConflictPlayers(player3,player4),false);
    QString str="hello";
    QVERIFY(str.toUpper()=="HELLO");
}


void TestController::test_howMuchHurt_data(){
    QTest::addColumn<int>("power");
   // QTest::addColumn<QPoint>("PlayerTwo");
    QTest::addColumn<int>("howMuchHurt");

    QTest::newRow("power 0")<<0<<1;
    QTest::newRow("power 2")<<2<<1;
    QTest::newRow("power 10")<<10<<1;
    QTest::newRow("power 11")<<11<<2;
    QTest::newRow("power 12")<<12<<2;
    QTest::newRow("power 90")<<90<<9;
    QTest::newRow("power 92")<<92<<10;
    QTest::newRow("power 100")<<100<<10;
     QTest::newRow("power 200")<<200<<10;
      QTest::newRow("power -100")<<-100<<1;

}
void TestController::test_howMuchHurt(){
    Data dat=Data();
    Controller contr(dat);
    QFETCH(int,power);
    QFETCH(int,howMuchHurt);
    //QFETCH(bool,is_colision);
    //QCOMPARE(contr.howMuchHurt(power),howMuchHurt);
}
