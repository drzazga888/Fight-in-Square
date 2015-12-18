#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include "../config.h"
#include "Game.h"
#include "Sprites.h"

class Drawer
{

public:
    Drawer(Game *game);
    void draw(QPainter *painter);

private:
    Game *game;
    Sprites sprites;

};

#endif // DRAWER_H
