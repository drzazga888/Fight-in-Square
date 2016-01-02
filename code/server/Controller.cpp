#include "Controller.h"
#include <QDebug>

Controller::Controller(Data &data)
    :data(data)
{
    // przyklad testowy
    // Swoja droga - ladowanie mapy NIE MOZE ODBYWAC SIE W KONTROLERZE!!!
    // Musi byc oddzielna klasa wywolywania, gdy serwer zacznie dzialac!
    // Obiekt tej nowej klasy MUSI sie znalezc jako pole w w obiekcie server.
    // data.model.board[1][2] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), true, 40);
    // data.model.board[7][9] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), false, 0);

    QPoint p = assignFreePosition();
    data.model.shots.append(Shot(0, p.x(), p.y(), assignDirection(), rand() % 20, INIT_POWER));
    p = assignFreePosition();
    data.model.shots.append(Shot(0, p.x(), p.y(), assignDirection(), rand() % 20, INIT_POWER));
    p = assignFreePosition();
    data.model.shots.append(Shot(0, p.x(), p.y(), assignDirection(), rand() % 20, INIT_POWER));

    BA(0, 0, DIRT);
    BA(0, 1, DIRT);
    BA(0, 2, GRASS);
    BA(0, 3, GRASS);
    BA(0, 4, GRASS);
    BA(0, 5, GRASS);
    BA(0, 6, GRASS);
    BA(0, 7, DIRT);
    BA(0, 8, DIRT);
    BA(0, 9, FLOWERGRASS);
    BA(0, 10, GRASS);
    BA(0, 11, GRASS);
    BA(0, 12, GRASS);
    BA(0, 13, GRASS);

    BA(1, 0, GRASS);
    BA(1, 1, GRASS);
    BA(1, 2, DIRT);
    BA(1, 3, GRASS);
    BA(1, 4, GRASS);
    BA(1, 5, GRASS);
    BA(1, 6, DIRT);
    BA(1, 7, DIRT);
    BA(1, 8, GRASS);
    BA(1, 9, GRASS);
    BA(1, 10, WALL);
    BA(1, 11, WALL);
    BA(1, 12, WALL);
    BA(1, 13, WALL);

    BA(2, 0, GRASS);
    BA(2, 1, GRASS);
    BA(2, 2, GRASS);
    BA(2, 3, DIRT);
    BA(2, 4, DIRT);
    BA(2, 5, DIRT);
    BA(2, 6, DIRT);
    BA(2, 7, DIRT);
    BA(2, 8, DIRT);
    BA(2, 9, FLOWERGRASS);
    BA(2, 10, GRASS);
    BA(2, 11, WALL);
    BA(2, 12, GRASS);
    BA(2, 13, GRASS);

    BA(3, 0, FLOWERGRASS);
    BA(3, 1, GRASS);
    BA(3, 2, GRASS);
    BA(3, 3, FLOWERGRASS);
    BA(3, 4, GRASS);
    BA(3, 5, GRASS);
    BA(3, 6, GRASS);
    BA(3, 7, DIRT);
    BA(3, 8, DIRT);
    BA(3, 9, DIRT);
    BA(3, 10, GRASS);
    BA(3, 11, WALL);
    BA(3, 12, GRASS);
    BA(3, 13, GRASS);

    BA(4, 0, FLOWERGRASS);
    BA(4, 1, WALL);
    BA(4, 2, WALL);
    BA(4, 3, WALL);
    BA(4, 4, WALL);
    BA(4, 5, WALL);
    BA(4, 6, GRASS);
    BA(4, 7, GRASS);
    BA(4, 8, FLOWERGRASS);
    BA(4, 9, DIRT);
    BA(4, 10, GRASS);
    BA(4, 11, GRASS);
    BA(4, 12, GRASS);
    BA(4, 13, GRASS);

    BA(5, 0, WALL);
    BA(5, 1, SAND);
    BA(5, 2, DIRT);
    BA(5, 3, DIRT);
    BA(5, 4, DIRT);
    BA(5, 5, WALL);
    BA(5, 6, GRASS);
    BA(5, 7, GRASS);
    BA(5, 8, GRASS);
    BA(5, 9, GRASS);
    BA(5, 10, GRASS);
    BA(5, 11, GRASS);
    BA(5, 12, GRASS);
    BA(5, 13, SAND);

    BA(6, 0, SAND);
    BA(6, 1, SAND);
    BA(6, 2, DIRT);
    BA(6, 3, WALL);
    BA(6, 4, DIRT);
    BA(6, 5, WALL);
    BA(6, 6, GRASS);
    BA(6, 7, GRASS);
    BA(6, 8, DIRT);
    BA(6, 9, DIRT);
    BA(6, 10, GRASS);
    BA(6, 11, SAND);
    BA(6, 12, SAND);
    BA(6, 13, SAND);

    BA(7, 0, SAND);
    BA(7, 1, SAND);
    BA(7, 2, DIRT);
    BA(7, 3, WALL);
    BA(7, 4, DIRT);
    BA(7, 5, WALL);
    BA(7, 6, GRASS);
    BA(7, 7, GRASS);
    BA(7, 8, GRASS);
    BA(7, 9, FLOWERGRASS);
    BA(7, 10, SAND);
    BA(7, 11, SAND);
    BA(7, 12, SAND);
    BA(7, 13, SAND);

    BA(8, 0, SAND);
    BA(8, 1, DIRT);
    BA(8, 2, WALL);
    BA(8, 3, WALL);
    BA(8, 4, WALL);
    BA(8, 5, WALL);
    BA(8, 6, WALL);
    BA(8, 7, WALL);
    BA(8, 8, SAND);
    BA(8, 9, SAND);
    BA(8, 10, SAND);
    BA(8, 11, SAND);
    BA(8, 12, WATER);
    BA(8, 13, WATER);

    BA(9, 0, DIRT);
    BA(9, 1, DIRT);
    BA(9, 2, DIRT);
    BA(9, 3, SAND);
    BA(9, 4, SAND);
    BA(9, 5, GRASS);
    BA(9, 6, GRASS);
    BA(9, 7, GRASS);
    BA(9, 8, SAND);
    BA(9, 9, WATER);
    BA(9, 10, WATER);
    BA(9, 11, WATER);
    BA(9, 12, WATER);
    BA(9, 13, WATER);


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
    return QPoint(rand() % (BOARD_COLS * BOARD_SUBFIELDS - 4) + 2, rand() % (BOARD_ROWS * BOARD_SUBFIELDS - 4) + 2);
}
