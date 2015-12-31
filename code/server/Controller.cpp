#include "Controller.h"
#include <QDebug>
#include <QVector>
#include "config.h"
#include "../shared/Model/Player.h"

//Controller::Controller():data(nullptr){}
Controller::Controller(Data &data)
    :data(data)
{
    playerInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        playerInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]=nullptr;
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
    QMap<int, Player> futuredPlayers=data.model.players;
    RefreshPlayerInBoard(futuredPlayers, playerInBoard);
    QMutableMapIterator<int,Player> it(futuredPlayers);
    while(it.hasNext()){
        it.next();
         it.value().direction=DIRECT(it.value().id);
         data.playerActions[it.value().id].moving_direction=NONE;
        movePlayer(it.value());
    }
    it.toFront();
    while(it.hasNext()){
        it.next();
        QMutableMapIterator<int,Player> it2(futuredPlayers);
        while(it2.hasNext()){
            it2.next();
            SolvePlayerConflict(it.value(),it2.value());
            qDebug() <<"Czy jest konflikt?"<<isConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y));
            qDebug() <<"Czy jest double konflikt?"<<isDoubleConflictPlayers(QPoint((int)it.value().x,(int)it.value().y),QPoint((int)it2.value().x,(int)it2.value().y));
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
    RefreshPlayerInBoard(futuredPlayers, playerInBoard);
    Board futuredBoard=data.model.board;

    QVector<Shot> futuredShots=data.model.shots;
    RefreshPlayerInBoard(futuredPlayers, playerInBoard);
    DebugDrawPlayerInBoard(playerInBoard);

    data.model.players=futuredPlayers;
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
        x=rand() % 5*BOARD_ROWS;
        y=rand() % 5*BOARD_COLS;
    }while(playerInBoard[x][y]!=nullptr);
    return QPoint(x, y);*/
    return QPoint(0,49);
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
    switch(player.direction){
    case UP:
        if(player.y==0)    player.direction=NONE;
        else    (player.y)--;
        break;
    case DOWN:
        if(player.y==(5*BOARD_ROWS-1))    player.direction=NONE;
        else    (player.y)++;
        break;
    case LEFT:
        if(player.x==0)    player.direction=NONE;
        else    (player.x)--;
        break;
    case RIGHT:
        if(player.x==(5*BOARD_COLS-1))    player.direction=NONE;
        else    (player.x)++;
        break;
    }
}
void Controller::backmovePlayer(Player & player){
    switch(player.direction){
    case UP:
                (player.y)++;
        player.direction=NONE;
        break;
    case DOWN:
                (player.y)--;
        player.direction=NONE;
        break;
    case LEFT:
                (player.x)++;
        player.direction=NONE;
        break;
    case RIGHT:
                (player.x)--;
        player.direction=NONE;
        break;
    }
}

void Controller::DebugDrawPlayerInBoard(QVector<QVector<Player*> > & playerInBoard){
    QString output="";
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            if(playerInBoard[i][j]==nullptr)
            output+= "0 ";
            else
                output+= "P ";
        }
        qDebug() <<output;
        qDebug() <<"--------"<<i<<"-------";
        output="";
    }
   // output="koniec tablicy";
    //qDebug() << output;
    //qDebug() <<"koniec tablicy";
}

void Controller::RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<Player*> > & playerInBoard){
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]=nullptr;
        }
    }
    QMutableMapIterator<int,Player> it(futuredPlayers);
    while(it.hasNext()){
        it.next();
        playerInBoard[it.value().y][it.value().x]=&it.value();
 /*!!!*/
    }
}

void Controller::SolvePlayerConflict(Player & player1,Player & player2){
    int odl_x=abs(player1.x-player2.x);
    int odl_y=abs(player1.y-player2.y);
    if(player1.direction==NONE || player2.direction==NONE){
        if(odl_x<=3 && odl_y<=3 && player1.direction==NONE)   backmovePlayer(player2);
        else if(odl_x<=3 && odl_y<=3 && player2.direction==NONE)  backmovePlayer(player1);

    }
    if(((player1.direction==LEFT && player1.direction==RIGHT) || (player1.direction==RIGHT && player1.direction==LEFT))||((player1.direction==UP && player1.direction==DOWN) || (player1.direction==DOWN && player1.direction==UP))){
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
        if(player1.direction==UP || player1.direction==DOWN){
            backmovePlayer(player1);
        }
        else{
            backmovePlayer(player2);
        }
    }
    else if(odl_y<=2 && odl_x==3){
        if(player1.direction==LEFT || player1.direction==RIGHT){
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
