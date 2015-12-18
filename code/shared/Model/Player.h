#ifndef PLAYER_H
#define PLAYER_H

#include "../../config.h"
#include "../../shared/Utils/Direction.h"
#include "../Frame/Frameable.h"

class Player: public Frameable
{

public:

	enum GROUP {
        RED_GROUP = 0,
        BLUE_GROUP = 1
	};

    Player();
    Player(int id, GROUP group, int x, int y, DIRECTION direction, QByteArray name);
    Player(int id, Player::GROUP group, int points, int health, int power, int x, int y, DIRECTION direction, QByteArray name);

    virtual void applyFrame(const QByteArray &frame);
    virtual QByteArray getFrame();

    unsigned char id;
	GROUP group;
    unsigned char points;
    unsigned char health;
    unsigned char power;
    unsigned char x;
    unsigned char y;
	DIRECTION direction;
    QByteArray name;

};

#endif
