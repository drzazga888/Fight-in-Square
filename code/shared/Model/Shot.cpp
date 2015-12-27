#include "Shot.h"

Shot::Shot()
    :player_id(0), x_start(0), y_start(0), direction(LEFT), flight_periods(0), power(INIT_POWER)
{
}

Shot::Shot(int player_id, int x_start, int y_start, DIRECTION direction, int flight_periods, int power)
    :player_id(player_id), x_start(x_start), y_start(y_start), direction(direction), flight_periods(flight_periods), power(power)
{
}

void Shot::applyFrame(const QByteArray &frame)
{
    player_id = frame[0];
    x_start = frame[1];
    y_start = frame[2];
    direction = (DIRECTION)frame[3];
    flight_periods = *((unsigned int *)(frame.data() + 4));
    power = frame[8];
}

QByteArray Shot::getFrame() const
{
    QByteArray frame(9, '\0');
    frame[0] = player_id;
    frame[1] = x_start;
    frame[2] = y_start;
    frame[3] = direction;
    frame[4] = flight_periods;
    frame[5] = flight_periods >> 8;
    frame[6] = flight_periods >> 16;
    frame[7] = flight_periods >> 24;
    frame[8] = power;
    return frame;
}
