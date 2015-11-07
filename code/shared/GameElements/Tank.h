#ifndef TANK_H
#define TANK_H

#include <QObject>
#include "BoardElement.h"
#include "../Player.h"

class Tank : public BoardElement
{
	Q_OBJECT
public:
	Tank(Player* p, Direction d);
	virtual Player* getPlayer() { return player; }
	virtual BoardElement::Direction getDirectin() { return dir; };
	virtual void addHealth(char h) { return player->addHealth(h); };
	virtual void takeHealth(char h) { return player->takeHealth(h); };
	virtual void setDirection(BoardElement::Direction d) { dir = d; };
	virtual char getHealth() { return player->getHealth() };
	virtual bool isIndestructible(){return false; };
	virtual void draw(char x, char y);
private:
	Direction dir;
	Player* player;
};

#endif