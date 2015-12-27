#include "Controller.h"
#include <QDebug>

Controller::Controller(Data &data)
    :data(data)
{
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
    // napisac!!!
    // przyklad testowy - kazdemu graczowi odejmuje
    // o 1 punkt zycia, jesli jest co odjac
    QMutableMapIterator<int, Player> i(data.model.players);
    while (i.hasNext())
    {
        i.next();
        qDebug() << "Przed: " << i.value().health;
        if (i.value().health)
            --i.value().health;
        qDebug() << "Po: " << i.value().health;
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
    // tak zeby dzialalo...
    return QPoint(0, 0);
}
