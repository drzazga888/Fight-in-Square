#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include "BoardElement.h"

class Obstacle : public BoardElement
{
	Q_OBJECT
public:
	Obstacle(char i, char h, bool ind=false);
	virtual void addHealth(char h){ health+=h; };
	virtual void takeHealth(char h){ health-=h; };
	virtual void setDirection(BoardElement::Direction::DirectionType d){ int i = (int)d;++i; };
	virtual char getHealth() { return health; };
	virtual bool isIndestructible() { return indestructible; };
	virtual void draw(char x, char y);
private:
	char health;
	bool indestructible;
};

#endif