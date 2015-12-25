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
    void paint_background(QPainter *painter,const Board &board); //throw(exception)

};

#endif // DRAWER_H
