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
 * Klasa służy do przechowywania obiektu animacji
 * jej stadium i położenia
 */
class Animation
{
public:
    Animation(int x, int y);
    int getPhase();
    int getplacex();
    int getplacey();
private:
    int x;
    int y;
    int step;
};


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
    QVector<Animation> animations;
    Game *game;
    Sprites sprites;
    void paint_background(QPainter *painter,const Board &board); //throw(exception)
    bool check_collisions(unsigned char x, unsigned char y, int type, DIRECTION direction);
    void which_field(int &col, int &row,int x, int y);
    void draw_players(QPainter *painter ,QMap<int, Player> players);
    void draw_bullets(QPainter *painter,QVector<Shot> shots);
};

#endif // DRAWER_H
