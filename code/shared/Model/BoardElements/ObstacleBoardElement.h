#ifndef OBSTACLEBOARDELEMENT_H
#define OBSTACLEBOARDELEMENT_H

#include "BoardElement.h"

class ObstacleBoardElement: public BoardElement
{

public:
    ObstacleBoardElement(int id, bool isDestructable, int health);
    virtual ~ObstacleBoardElement(){}

    bool isDestructable;
    int health;

};

#endif // OBSTACLEBOARDELEMENT_H
