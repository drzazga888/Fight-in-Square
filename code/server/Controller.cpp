#include "Controller.h"
#include <QDebug>
#include <QVector>
#include "config.h"
#include "../shared/Model/Player.h"


Controller::Controller(Data &data)
    :data(data)
{
    playerInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        playerInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]='0';
        }
    }
    shotInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        shotInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<shotInBoard.size();i++){
        for(int j=0;j<shotInBoard.operator[](i).size();j++){
            shotInBoard[i][j]=0;
        }
    }
    // przyklad testowy
    // Swoja droga - ladowanie mapy NIE MOZE ODBYWAC SIE W KONTROLERZE!!!
    // Musi byc oddzielna klasa wywolywania, gdy serwer zacznie dzialac!
    // Obiekt tej nowej klasy MUSI sie znalezc jako pole w w obiekcie server.
    data.model.board[1][2] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), true, 40);
    data.model.board[7][9] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), false, 0);
}

Player &Controller::addPlayer(int id, QByteArray name)
{
    QPoint freePosition = assignFreePosition();
    data.model.players.insert(id, Player(id, assignGroup(), freePosition.x(), freePosition.y(), assignDirection(), name));
    data.playerActions.insert(id, PlayerAction(id));
    return data.model.players[id];
}

void Controller::removePlayer(int id)
{
    data.model.players.remove(id);
    data.playerActions.remove(id);
}

void Controller::nextModelStatus()
{
    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    QMutableMapIterator<int,Player> it(data.model.players);
    while(it.hasNext()){
        it.next();
        movePlayer(it.value());
    }
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(!it.hasNext())   break;
        QMutableMapIterator<int,Player> it2(data.model.players);
        while(it2.hasNext()){
            it2.next();
            SolvePlayerConflict(it.value(),it2.value());
          //  qDebug() <<"Czy jest konflikt?"<<isConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y));
          //  qDebug() <<"Czy jest double konflikt?"<<isDoubleConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y));
/*
            if(it2.value().id!=it.value().id && isConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y))){
                if(it2.value().id!=it.value().id && isDoubleConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y))){
                    backmovePlayer(it2.value());
                    backmovePlayer(it.value());
                }
                else if(it2.value().direction==NONE)    backmovePlayer(it.value());
                else if(it.value().direction==NONE) backmovePlayer(it2.value());
                //it.toBack();
            }
*/        }

  //      it.value().direction=NONE;
    }
    Board futuredBoard=data.model.board;
    it.toFront();
    //teraz pociski !!!
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(IS_SHOT(it.value().id)==true && it.value().is_alive){
            data.model.shots.append(Shot(it.value().id,it.value().x,it.value().y,it.value().direction,0,it.value().power));
        }
    }
    it.toFront();
    for(QVector<Shot>::iterator i=data.model.shots.begin();i!=data.model.shots.end();/*i++*/){
        // przesuwamy je !!
        i->flight_periods++;
        int howMuchShoted=0;
        while(it.hasNext()){
            it.next();
            //czy zestrzelilisny gracza ; siebie samego zestrzelic nie mozemy
            if(it.value().is_alive && it.value().id!=i->player_id && isShotInPlayer(getActualShotPosition(*i),QPoint(it.value().x,it.value().y))){
                howMuchShoted++;
                data.model.players.value(i->player_id).points;
                if((it.value().health-howMuchHurt(i->power))<=0)    {
                    it.value().health=0;
                    it.value().is_alive=false;
                    it.value().death_time=0;

                    //if(it.value().points-1<0) it.value().points=0;
                   // else    it.value().points-=1;
                    data.model.players[i->player_id].points++;
                    data.model.players[i->player_id].power++;
                }
                else{
                    it.value().health-=howMuchHurt(i->power);
                }

            }
        }
        it.toFront();
        if(howMuchShoted>0){
            i=data.model.shots.erase(i);
        }
        else if(!isShotInBoard(QPoint(getActualShotPosition(*i)))){
            i=data.model.shots.erase(i);
        }
        else{
            i++;
        }
    }
    //teraz zajmujemy się trupami
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(it.value().is_alive==false){
            if(it.value().death_time<REGENERATION_TIME){
                it.value().death_time++;
            }
            else{
                QPoint freePosition = assignFreePosition();
                it.value().is_alive=true;
                it.value().death_time=0;
                it.value().health=MAX_HEALTH;
                it.value().direction=assignDirection();
                it.value().x=freePosition.x();
                it.value().y=freePosition.y();
             }
        }
    }
    //"zerujemy"
    it.toFront();
    while(it.hasNext()){
        it.next();
        DIRECT(it.value().id)=NONE;
        IS_SHOT(it.value().id)=false;
    }
    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    debugDrawInBoard(playerInBoard,shotInBoard);
}

Player::GROUP Controller::assignGroup()
{
    int reds = 0, blues = 0;
    QMapIterator<int, Player> i(data.model.players);
    while (i.hasNext())
    {
        i.next();
        switch (i.value().group)
        {
        case Player::RED_GROUP:
            ++reds;
            break;
        case Player::BLUE_GROUP:
            ++blues;
            break;
        }
    }
    if (reds < blues)
        return Player::RED_GROUP;
    else if (reds > blues)
        return Player::BLUE_GROUP;
    else
        return (Player::GROUP)(rand() % 2);
}

DIRECTION Controller::assignDirection()
{
    return (DIRECTION)(rand() % 4 + 1);
}

QPoint Controller::assignFreePosition(){
   /* int x=0;int y=0;
    do{
        x=rand() % (5*BOARD_ROWS-2)+2;
        y=rand() % (5*BOARD_COLS-2)+2;
    }while(playerInBoard[x][y]!=nullptr);
    return QPoint(x, y);*/
    return QPoint(2,45);
}

bool Controller::isConflictPlayers(QPoint player1,QPoint player2){
    int odl_x=abs(player1.x()-player2.x());
    int odl_y=abs(player1.y()-player2.y());
    if(odl_x<4 && odl_y<4)  return true;
    else return false;
}
bool Controller::isDoubleConflictPlayers(QPoint player1,QPoint player2){
    int odl_x=abs(player1.x()-player2.x());
    int odl_y=abs(player1.y()-player2.y());
    if((odl_x<3 && odl_y<4) || (odl_x<4 && odl_y<3))  return true;
    else return false;
}
void Controller::movePlayer(Player & player){
    if(!player.is_alive)    return;
    if(DIRECT(player.id)!=NONE) player.direction=DIRECT(player.id); //nawet, jeśli nie uda się przesunąc, to kierunek czołgu zmieniamy!
    switch(DIRECT(player.id)){
    case UP:
        if(player.y==2)    DIRECT(player.id)=NONE;
        else    (player.y)--;
        break;
    case DOWN:
        if(player.y==(5*BOARD_ROWS-1-2))    DIRECT(player.id)=NONE;
        else    (player.y)++;
        break;
    case LEFT:
        if(player.x==2)    DIRECT(player.id)=NONE;
        else    (player.x)--;
        break;
    case RIGHT:
        if(player.x==(5*BOARD_COLS-1-2))    DIRECT(player.id)=NONE;
        else    (player.x)++;
        break;
    }
}
void Controller::backmovePlayer(Player & player){
    if(!player.is_alive)    return;
    switch(DIRECT(player.id)){
    case UP:
                (player.y)++;
        DIRECT(player.id)=NONE;
        break;
    case DOWN:
                (player.y)--;
        DIRECT(player.id)=NONE;
        break;
    case LEFT:
                (player.x)++;
        DIRECT(player.id)=NONE;
        break;
    case RIGHT:
                (player.x)--;
        DIRECT(player.id)=NONE;
        break;
    }
}

void Controller::debugDrawInBoard(QVector<QVector<char> > & playerInBoard, QVector<QVector<int> >& shotInBoard){
    QString output="";
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            if(shotInBoard[i][j]==0 && playerInBoard[i][j]=='P') output+="P ";
            else if(shotInBoard[i][j]==0 && playerInBoard[i][j]=='W')   output+="W ";
            else{
                QString str=QString::number(shotInBoard[i][j]);
                output=output+str+' ';
            }
        }
        qDebug() <<output;
        //qDebug() <<"--------"<<i<<"-------";
        output="";
    }
   // output="koniec tablicy";
    //qDebug() << output;
    qDebug() <<"koniec tablicy";
}

void Controller::RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<char> > & playerInBoard){
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]='0';
        }
    }
    QMutableMapIterator<int,Player> it(futuredPlayers);
    while(it.hasNext()){
        it.next();
        if(it.value().is_alive){
            for(int i=it.value().y-2;i<=it.value().y+2;i++) {

                for(int j=it.value().x-2;j<=it.value().x+2;j++){
                    playerInBoard[i][j]='P';
                }
            }
            playerInBoard[it.value().y][it.value().x]='W';
        }
    }
 /*!!!*/
}
void Controller::refreshShotInBoard(QVector<Shot> futuredShots,QVector<QVector<int> > & shotInBoard){
    for(int i=0;i<shotInBoard.size();i++){
        for(int j=0;j<shotInBoard.operator[](i).size();j++){
            shotInBoard[i][j]=0;
        }
    }
    for(int i=0;i<futuredShots.size();i++){
        shotInBoard[getActualShotPosition(futuredShots[i]).y()][getActualShotPosition(futuredShots[i]).x()]++;
    }
 /*!!!*/
}


void Controller::SolvePlayerConflict(Player & player1,Player & player2){
    if(!player1.is_alive)    return;
    if(!player2.is_alive)    return;
    int odl_x=abs(player1.x-player2.x);
    int odl_y=abs(player1.y-player2.y);
    if(DIRECT(player1.id)==NONE || DIRECT(player2.id)==NONE){
        if(odl_x<=3 && odl_y<=3 && DIRECT(player1.id)==NONE)   backmovePlayer(player2);
        else if(odl_x<=3 && odl_y<=3 && DIRECT(player2.id)==NONE)  backmovePlayer(player1);

    }
    if(((DIRECT(player1.id)==LEFT && DIRECT(player2.id)==RIGHT) || (DIRECT(player1.id)==RIGHT && DIRECT(player2.id)==LEFT))||((DIRECT(player1.id)==UP && DIRECT(player2.id)==DOWN) || (DIRECT(player1.id)==DOWN && DIRECT(player2.id)==UP))){
        if(((odl_x==3 && odl_y==3) ||(odl_y==3 && odl_x==3)) ){
            backmovePlayer(player1);
        }
        else if(((odl_x==2 && odl_y<=3) ||(odl_y==2 && odl_x<=3)) ){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
    }
    else if(odl_x==3 && odl_y==3){
        backmovePlayer(player1);
    }
    else if(odl_x<=2 && odl_y==3){
        if(DIRECT(player1.id)==UP || DIRECT(player1.id)==DOWN){
            backmovePlayer(player1);
        }
        else{
            backmovePlayer(player2);
        }
    }
    else if(odl_y<=2 && odl_x==3){
        if(DIRECT(player1.id)==LEFT || DIRECT(player1.id)==RIGHT){
            backmovePlayer(player1);
        }
        else{
            backmovePlayer(player2);
        }
    }
    else if(odl_y==2 && odl_x==2){
        backmovePlayer(player1);
        backmovePlayer(player2);
    }
}

bool Controller::isShotInPlayer(QPoint shot,QPoint player){
    int odl_x=abs(shot.x()-player.x());
    int odl_y=abs(shot.y()-player.y());
    if(odl_x<=2 && odl_y<=2)  return true;
    else return false;
}

QPoint Controller::getActualShotPosition(const Shot & shot){
    switch(shot.direction){
    case UP:
        return QPoint(shot.x_start,shot.y_start-shot.flight_periods);
        break;
    case DOWN:
        return QPoint(shot.x_start,shot.y_start+shot.flight_periods);
        break;
    case LEFT:
        return QPoint(shot.x_start-shot.flight_periods,shot.y_start);
        break;
    case RIGHT:
        return QPoint(shot.x_start+shot.flight_periods,shot.y_start);
        break;
    default:
        return QPoint(-1,-1);
    }
}

bool Controller::isShotInBoard(const QPoint &shot){
    if(shot.x()>=0 && shot.x()<=(5*BOARD_COLS-1) && shot.y()>=0 && shot.y()<=(5*BOARD_ROWS-1))  return true;
    else return false;
}

int Controller::howMuchHurt(int power){
    if(power>100)   return 10;
    else if(power<0)    return 1;
    int hurt=(power-1)/10 +1;
    return hurt;
}
