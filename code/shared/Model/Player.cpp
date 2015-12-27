#include "Player.h"
#include <QDebug>

Player::Player()
    :id(0), group(Player::BLUE_GROUP), points(0), health(MAX_HEALTH), power(INIT_POWER), x(0), y(0), direction(RIGHT), name("Bezimienny"), is_alive(true), death_time(0)
{
}

Player::Player(int id, Player::GROUP group, int x, int y, DIRECTION direction, QByteArray name)
    :id(id), group(group), points(0), health(MAX_HEALTH), power(INIT_POWER), x(x), y(y), direction(direction), name(name), is_alive(true), death_time(0)
{
}

Player::Player(int id, Player::GROUP group, int points, int health, int power, int x, int y, DIRECTION direction, QByteArray name, bool is_alive, int death_time)
    :id(id), group(group), points(points), health(health), power(power), x(x), y(y), direction(direction), name(name), is_alive(is_alive), death_time(death_time)
{
}

Player::Player(QByteArray frame)
{
    applyFrame(frame);
}

void Player::applyFrame(const QByteArray &frame)
{
    id = frame[0];
    group = (Player::GROUP)frame[1];
    points = frame[2];
    health = frame[3];
    power = frame[4];
    x = frame[5];
    y = frame[6];
    direction = (DIRECTION)frame[7];
    is_alive = frame[24];
    death_time = frame[25];
    name = QByteArray(frame.data() + 8);
}

QByteArray Player::getFrame() const
{
    QByteArray frame(26, '\0');
    frame[0] = id;
    frame[1] = group;
    frame[2] = points;
    frame[3] = health;
    frame[4] = power;
    frame[5] = x;
    frame[6] = y;
    frame[7] = direction;
    frame.insert(8, name);
    frame[24] = is_alive;
    frame[25] = death_time;
    frame.resize(26);
    qDebug() << id << ": " << health;
    return frame;
}
