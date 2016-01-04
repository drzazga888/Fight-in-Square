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
 bool Shot::operator==( const Shot & dane) const{
    if(player_id==dane.player_id && x_start==dane.x_start && y_start==dane.y_start && direction==dane.direction && (flight_periods-dane.flight_periods)<=3*SPEEDSHOT && power==dane.power)    return true;
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

