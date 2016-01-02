#ifndef ANIMATION_H
#define ANIMATION_H

/**
 * @brief
 * Klasa służy do przechowywania obiektu animacji
 * jej stadium i położenia
 */
class Animation
{
public:
    Animation();
    Animation(int x, int y);
    int getPhase();
    int getplacex();
    int getplacey();
private:
    int x;
    int y;
    int step;
};

#endif // ANIMATION_H
