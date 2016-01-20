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
    Animation(int x, int y,int st=10);
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
