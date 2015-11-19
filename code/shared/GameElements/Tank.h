#ifndef TANK_H
#define TANK_H

#include <QObject>
#include "BoardElement.h"
#include "../Player.h"

class Tank : public BoardElement
{
	Q_OBJECT
public:
	Tank(Player* p, BoardElement::Direction::DirectionType d);
	virtual Player* getPlayer() { return player; }
	virtual BoardElement::Direction::DirectionType getDirection() { return dir; };
	virtual void addHealth(char h) { player->addHealth(h); };
	virtual void takeHealth(char h) { player->takeHealth(h); };
	virtual void setDirection(BoardElement::Direction::DirectionType d) { dir = d; };
	virtual char getHealth() { return player->getHealth(); };
	virtual bool isIndestructible(){return false; };
	virtual void draw(char x, char y);
private:
	BoardElement::Direction::DirectionType dir;
	Player* player;
};

#endif
