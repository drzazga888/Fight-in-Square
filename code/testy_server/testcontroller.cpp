#include "testcontroller.h"


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
    QCOMPARE(contr.howMuchHurt(power),howMuchHurt);
}

Q_DECLARE_METATYPE (DIRECTION)
void TestController::test_conflictPlayers_data(){

    QTest::addColumn<int>("x_pocz");
    QTest::addColumn<int>("y_pocz");
    QTest::addColumn<DIRECTION>("move_direct");
    QTest::addColumn<DIRECTION>("direct");
    QTest::addColumn<int>("x_kon");
    QTest::addColumn<int>("y_kon");
    QTest::addColumn<int>("x_pocz2");
    QTest::addColumn<int>("y_pocz2");
    QTest::addColumn<DIRECTION>("move_direct2");
    QTest::addColumn<DIRECTION>("direct2");
    QTest::addColumn<int>("x_kon2");
    QTest::addColumn<int>("y_kon2");
   // QTest::addColumn<QPoint>("PlayerTwo");

    QTest::newRow("sa obok siebie")<<26<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<26<<40<<31<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<31<<40;
    QTest::newRow("nakladaja sie single RIGHT LEFT")<<26<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<26<<40<<30<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<31<<40;
    QTest::newRow("nakladaja sie double RIGHT LEFT")<<26<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<25<<40<<29<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<30<<40;
    QTest::newRow("sa obok siebie DOWN UP")<<30<<39<<DIRECTION::DOWN<<DIRECTION::DOWN<<30<<39<<30<<44<<DIRECTION::UP<<DIRECTION::UP<<30<<44;
    QTest::newRow("nakladaja sie single DOWN UP")<<30<<39<<DIRECTION::DOWN<<DIRECTION::DOWN<<30<<39<<30<<43<<DIRECTION::UP<<DIRECTION::UP<<30<<44;
    QTest::newRow("nakladaja sie double DOWN UP")<<30<<39<<DIRECTION::DOWN<<DIRECTION::DOWN<<30<<38<<30<<42<<DIRECTION::UP<<DIRECTION::UP<<30<<43;
    QTest::newRow("nakladaja sie odwraca sie z prawo na lewo; idzie na lewo")
            <<30<<40<<DIRECTION::NONE<<DIRECTION::LEFT<<30<<40<<33<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<34<<40;
    QTest::newRow("nakladaja sie odwraca sie z lewo na prawo; idzie na lewo")
            <<30<<40<<DIRECTION::NONE<<DIRECTION::RIGHT<<30<<40<<33<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<34<<40;
    QTest::newRow("nakladaja sie RIGHT DOWN single")
            <<30<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<29<<40<<33<<37<<DIRECTION::DOWN<<DIRECTION::DOWN<<33<<37;
    QTest::newRow("nakladaja sie RIGHT DOWN double")
            <<30<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<30<<40<<32<<37<<DIRECTION::DOWN<<DIRECTION::DOWN<<32<<36;
    QTest::newRow("nakladaja sie LEFT UP single")
            <<30<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<31<<40<<27<<37<<DIRECTION::UP<<DIRECTION::UP<<27<<37;
    QTest::newRow("nakladaja sie UP LEFT single")
            <<27<<37<<DIRECTION::UP<<DIRECTION::UP<<27<<37<<30<<40<<DIRECTION::LEFT<<DIRECTION::LEFT<<31<<40;
    //QTest::newRow("nakladaja sie RIGHT UP double")
      //      <<29<<40<<DIRECTION::RIGHT<<DIRECTION::RIGHT<<31<<40<<28<<37<<DIRECTION::UP<<DIRECTION::UP<<32<<36;

}
void TestController::test_conflictPlayers(){
    QFETCH(int,x_pocz);
    QFETCH(int,y_pocz);
    QFETCH(int,x_pocz2);
    QFETCH(int,y_pocz2);
    QFETCH(DIRECTION,move_direct);
    QFETCH(DIRECTION,move_direct2);
    QFETCH(DIRECTION,direct);
    QFETCH(DIRECTION,direct2);
    QFETCH(int,x_kon);
    QFETCH(int,y_kon);
    QFETCH(int,x_kon2);
    QFETCH(int,y_kon2);

    Data dat=Data();
    dat.playerActions.insert(1,PlayerAction(false,move_direct,1));
    dat.playerActions.insert(2,PlayerAction(false,move_direct2,2));
    Controller contr(dat);
    Loader loader;
    loader.SetFilePathName("../server/maps/empty.map");
    loader.loadIDMapFromFile();
    contr.loadExtendedBoard(loader.getIdBoard());
    Player player1=Player(1,Player::GROUP::BLUE_GROUP,x_pocz,y_pocz,direct,"Zbynio");
    Player player2=Player(2,Player::GROUP::RED_GROUP,x_pocz2,y_pocz2,direct2,"Stasio");
    //contr.addPlayer(1,Player(1,Player::GROUP::BLUE_GROUP,x_pocz,y_pocz,direct,"Zbynio"));
    //contr.addPlayer(2,Player(2,Player::GROUP::RED_GROUP,x_pocz2,y_pocz2,direct2,"Stasio"));
    contr.SolvePlayerConflict(player1,player2);

    //QFETCH(bool,is_colision);
    //int play1x=
    QCOMPARE(static_cast<int>(player1.x),x_kon);
    QCOMPARE(static_cast<int>(player1.y),y_kon);
    QCOMPARE(static_cast<int>(player2.x),x_kon2);
    QCOMPARE(static_cast<int>(player2.y),y_kon2);


}
