#include "animation.h"
#include <QDebug>

Animation::Animation(int x, int y, int st): step(st), x(x), y(y)
{
}
Animation::Animation(): step(BOOM_1_BOARD_FIELD_ID), x(0),  y(0)
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
   switch (step) {
    case BOOM_3_BOARD_FIELD_ID:
        step=EMPTY_BOARD_FIELD_ID;
        break;
    case BOOM_2_BOARD_FIELD_ID:
        step=BOOM_3_BOARD_FIELD_ID;
        break;
    case BOOM_1_BOARD_FIELD_ID:
        step=BOOM_2_BOARD_FIELD_ID;
        break;
    default:
        break;
    }
}
