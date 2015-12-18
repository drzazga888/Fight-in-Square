#include "Controller.h"
#include <QDebug>

Controller::Controller(Model &model)
    :model(model)
{
    // for debug only
    model.board[1][2] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), true, 40);
    model.board[7][9] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), false, 0);
}

Player &Controller::addPlayer(int id, QByteArray name)
{
    QPoint freePosition = assignFreePosition();
    model.players.append(Player(id, assignGroup(), freePosition.x(), freePosition.y(), assignDirection(), name));
    return model.players.last();
}

void Controller::removePlayer(int id)
{
    for (int i = 0; i < model.players.size(); ++i)
    {
        if (model.players[i].id == id){
            model.players.remove(i);
            return;
        }
    }
    qDebug() << "Gracz ktorego chcesz usunac, nie istnieje, id = " << id;
}

void Controller::nextModelStatus()
{
    // napisac!!!
}

Player::GROUP Controller::assignGroup()
{
    int reds = 0, blues = 0;
    for (int i = 0; i < model.players.size(); ++i)
    {
        switch (model.players[0].group)
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
