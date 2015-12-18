#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QPoint>
#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "../shared/Model/Model.h"
#include "../shared/Model/BoardElements/ObstacleBoardElement.h"

class Controller
{

public:
    Controller(Model &model);
    Player &addPlayer(int id, QByteArray name);
    void removePlayer(int id);
    void nextModelStatus();

private:
    Player::GROUP assignGroup();
    DIRECTION assignDirection();
    QPoint assignFreePosition();
    Model model;

};

#endif // CONTROLLER_H
