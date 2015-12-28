#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include "../config.h"
#include "Game.h"
#include "Sprites.h"

#define BULLET_TYPE 0
#define TUNK_TYPE 1

/**
 * @brief
 * Klasa służy do malowania planszy, czołgów i pocisków
 * na podstawie obiektu game.
 */
class Drawer
{

public:
    Drawer(Game *game);

    /**
     * @brief
     * Główna funkjca malująca - używa game i painter
     * do namalowania planszy.
     * @param painter
     * Obiekt, który daje interfejs do malowania
     */
    void draw(QPainter *painter);

private:
    Game *game;
    Sprites sprites;
    void paint_background(QPainter *painter,const Board &board); //throw(exception)
    bool check_collisions(unsigned char x, unsigned char y, int type, DIRECTION direction);
    void which_field(int &col, int &row,int x, int y);
    void draw_players(QPainter *painter ,QMap<int, Player> players);
};

#endif // DRAWER_H
