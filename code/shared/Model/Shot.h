#ifndef SHOT_H
#define SHOT_H

#include "../../config.h"
#include "../Utils/Direction.h"
#include "../Frame/Frameable.h"

class Shot: public Frameable
{

public:

    Shot();
	Shot(int player_id, int x_start, int y_start, DIRECTION direction, int flight_periods, int power);

    virtual void applyFrame(const QByteArray &frame);
    virtual QByteArray getFrame();

    unsigned char player_id;
    unsigned char x_start;
    unsigned char y_start;
	DIRECTION direction;
    unsigned int flight_periods;
    unsigned char power;

};

#endif
