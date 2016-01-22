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
    int getPhase();
    void changePhase();
    int getplacex();
    int getplacey();
private:
    int step;
    int x;
    int y;

};

#endif // ANIMATION_H
