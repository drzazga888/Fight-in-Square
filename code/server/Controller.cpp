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
        for(int j=0;j<playerInBoard[i].size();j++){
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

    QMutableMapIterator<int,Player> it(data.model.players);
    while(it.hasNext()){
        it.next();
        playerInBoard[it.value().x][it.value().y]=&it.value();
    }

    Board futuredBoard=data.model.board;
    QMap<int, Player> futuredPlayers=data.model.players;
    QVector<Shot> futuredShots=data.model.shots;

    QString output="";
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard[i].size();j++){
            if(playerInBoard[i][j]==nullptr)
            output+= "0 ";
            else
                output+= "P ";
        }
        qDebug() <<output;
    }
    output="koniec tablicy";
    qDebug() <<output;

    // napisac!!!
    // przyklad testowy - kazdemu graczowi odejmuje
    // o 1 punkt zycia, jesli jest co odjac
    QMutableMapIterator<int, Player> i(data.model.players);
    while (i.hasNext())
    {
        i.next();
        qDebug() << "Wartość key " << i.key();
        /*qDebug() << "Przed: " << i.value().health;
        if (i.value().health)
            --i.value().health;
        qDebug() << "Po: " << i.value().health;
        */
}
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
    int x=0;int y=0;
    do{
        x=rand() % 5*BOARD_ROWS;
        y=rand() % 5*BOARD_COLS;
    }while(playerInBoard[x][y]!=nullptr);
    return QPoint(x, y);
}

bool Controller::isConflictPlayers(QPoint player1,QPoint player2){
    int odl_x=abs(player1.x()-player2.x());
    int odl_y=abs(player1.y()-player2.y());
    if(odl_x<4 && odl_y<4)  return true;
    else return false;
}


