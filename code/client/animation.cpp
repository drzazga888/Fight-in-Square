#include "animation.h"

Animation::Animation(int x, int y): x(x), y(y), step(10)
{
}

Animation::Animation(): x(0), y(0), step(10)
{
}

int Animation::getPhase()
{
    if(step<13)
    {
    ++step;
    return step-1;
    }
    else
        return 0;
}

int Animation::getplacex()
{
    return x;
}

int Animation::getplacey()
{
    return y;
}


