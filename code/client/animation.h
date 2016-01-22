#ifndef ANIMATION_H
#define ANIMATION_H

#include "../config.h"

/**
 * @brief
 * Klasa służy do przechowywania obiektu animacji
 * jej stadium i położenia
 */
class Animation
{
public:
    Animation();
    Animation(int x, int y,int st=BOOM_1_BOARD_FIELD_ID);

    /**
     * @brief getPhase
     * getter dla fazy animacji
     * @return stadium w którym aktualnie znajduje się animacja
     */
    int getPhase();

    /**
     * @brief changePhase
     * funkcja służąca do zmieniania fazy animacji na kolejną
     */
    void changePhase();

    /**
     * @brief getplacex
     * getter dla położenia animacji w poziomie
     * @return zwraca położenie animacji w poziomie w pixelach
     */
    int getplacex();

    /**
     * @brief getplacey
     * getter dla położenia animacji w pionie
     * @return zwraca położenie animacji w pionie w pixelach
     */
    int getplacey();
private:
    int step;
    int x;
    int y;

};

#endif // ANIMATION_H
