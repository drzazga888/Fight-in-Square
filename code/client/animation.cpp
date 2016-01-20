#include "animation.h"

Animation::Animation(int x, int y, int st): x(x), y(y), step(st)
{
}
Animation::Animation(): x(0), y(0), step(10)
{
}

int Animation::getPhase()
{
    return step;
}

int Animation::getplacex()
{
    return x;
}

int Animation::getplacey()
{
    return y;
}

void Animation::changePhase(){
    if(step < 12 && step >0)
        step+=1;
    else
        step=0;
}
