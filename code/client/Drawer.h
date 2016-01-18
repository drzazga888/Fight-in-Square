#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include "../config.h"
#include "Game.h"
#include "Sprites.h"
#include "animation.h"


/**
 * @brief
 * Klasa służy do malowania planszy, czołgów i pocisków
 * na podstawie obiektu game.
 */
class Drawer
{

public:
    Drawer(Game *game);

    enum TYPE{
        TUNK_TYPE=1,
        BULLET_TYPE=0
    };

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

    /**
     * @brief
     * funkcja służy do malowania statycznych elementów planszy
     * @param painter
     * Obiekt, który daje interfejs do malowania
     * @param board
     * tablica statycznych obiektów planszy
     */
    void paint_background(QPainter *painter,const Board &board); //throw(exception)


    /**
     * @brief check_collisions
     * funkcja sprwdzająca zajście kolizji
     * @param x
     * współrzędna x przemieszczającego się obiektu
     * @param y
     * współrzędna y przemieszczającego się obiektu
     * @param type
     * typ lecącego obiektu - możliwy typ zderzenia
     * @param direction
     * kierunek w którym porusza się obiekt
     * @return
     * prawda gdy dojdzie do zderzenia, fałsz, gdy nie dojdzie
     */
    bool check_collisions(unsigned char x, unsigned char y, int type, DIRECTION direction);

    /**
     * @brief
     * funkcja sprawdzająca w którym polu (kolumnie i wierszu) znajduje się przekazany punkt
     * @param col
     * zmienna, do której zapisywany jest numer kolumny
     * @param row
     * zmienna, do której zapisywany jest numer wiersza
     * @param x
     * położenie punktu w poziomie, w pixelach
     * @param y
     * położenie punktu w pionie, w pixelach
     */
    void which_field(int &col, int &row,int x, int y);

    /**
     * @brief draw_players
     * funkcja odpowiadająca za rysowanie graczy
     * @param painter
     * Obiekt, który daje interfejs do malowania
     * @param players1
     * tablica graczy z pierwszego modelu
     * @param players2
     * tablica graczy z drugiego modelu
     * @param phase
     * procentowy wskaźnik zamiany pierwszego modelu na drugi
     */
    void draw_players(QPainter *painter ,QMap<int, Player> players1, QMap<int, Player> players2, float phase);

    /**
     * @brief draw_bullets
     * funkcja rysująca lecące pociski
     * @param painter
     * Obiekt, który daje interfejs do malowania
     * @param shots
     * vector pocisków
     */
    void draw_bullets(QPainter *painter,QVector<Shot> &shots);

    /**
     * @brief cast_to_pixels
     * funkcja rzutująca pozycje w grze na pixele na obszarze rysowania
     * @param x
     * pozycja w grze
     * @return
     * pixele w których mieści się obiekt o pozycji x
     */
    int cast_to_pixels(int x);
};

#endif // DRAWER_H
