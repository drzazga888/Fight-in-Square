#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include "BoardElement.h"

class Obstacle : public BoardElement
{
	Q_OBJECT
public:
	Obstacle(i, h, ind=false);
	virtual void addHealth(char h){ health+=h; };
	virtual void takeHealth(char h){ health-=h; };
	virtual void setDirection(BoardElement::Direction d){ };
	virtual char getHealth() { return health; };
	virtual bool isIndestructible() { return indestructible; };
	virtual void draw(char x, char y);
private:
	char health;
	bool indestructible;
};

#endif