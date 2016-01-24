#include "Shot.h"

Shot::Shot()
    :id(0), player_id(0), x_start(0), y_start(0), direction(LEFT), flight_periods(0), power(INIT_POWER)
{
}

Shot::Shot(int id, int player_id, int x_start, int y_start, DIRECTION direction, int flight_periods, int power)
    :id(id), player_id(player_id), x_start(x_start), y_start(y_start), direction(direction), flight_periods(flight_periods), power(power)
{
}

Shot::Shot(const QByteArray &frame)
{
    applyFrame(frame);
}

void Shot::applyFrame(const QByteArray &frame)
{
    id = frame[0];
    player_id = frame[1];
    x_start = frame[2];
    y_start = frame[3];
    direction = (DIRECTION)frame[4];
    flight_periods = *((unsigned int *)(frame.data() + 5));
    power = frame[9];
}

QByteArray Shot::getFrame() const
{
    QByteArray frame(10, '\0');
    frame[0] = id;
    frame[1] = player_id;
    frame[2] = x_start;
    frame[3] = y_start;
    frame[4] = direction;
    frame[5] = flight_periods;
    frame[6] = flight_periods >> 8;
    frame[7] = flight_periods >> 16;
    frame[8] = flight_periods >> 24;
    frame[9] = power;
    return frame;
}

bool Shot::operator==( const Shot & dane) const{
    if(player_id==dane.player_id && x_start==dane.x_start && y_start==dane.y_start && direction==dane.direction && (flight_periods-dane.flight_periods)<=SHOTINTERVAL*SPEEDSHOT)    return true;
    else return false;
}

bool Shot::operator%=(  Shot & dane) const{
    if(player_id!=dane.player_id && abs(getActualShotPosition().x()-dane.getActualShotPosition().x())<=SPEEDSHOT-1 && abs(getActualShotPosition().y()-dane.getActualShotPosition().y())<=SPEEDSHOT-1)    return true;
    else return false;
}

QPoint Shot::getActualShotPosition() const{
     switch(direction){
     case UP:
         return QPoint(x_start,y_start-flight_periods);
         break;
     case DOWN:
         return QPoint(x_start,y_start+flight_periods);
         break;
     case LEFT:
         return QPoint(x_start-flight_periods,y_start);
         break;
     case RIGHT:
         return QPoint(x_start+flight_periods,y_start);
         break;
     default:
         return QPoint(-1,-1);
     }
 }

