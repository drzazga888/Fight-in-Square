#ifndef BOARD_ELEMENT_H
#define BOARD_ELEMENT_H

#include <QObject>
#include "../Player.h"

class BoardElement : public QObject
{
	Q_OBJECT
public:
	class BoardType
	{
	public:
		enum Type { Blank, Tank, Obstacle };
	};
	class Direction
	{
	public:
		enum DirectionType {None, Up, Down, Right, Left};
	};
	BoardElement(char i){ id = i; }
	virtual char getId() { return id; }
	virtual BoardElement::BoardType::Type getType(){ return type; }
	virtual void addHealth(char h) = 0;
	virtual void takeHealth(char h) = 0;
	virtual void setDirection(BoardElement::Direction::DirectionType d) = 0;
	virtual Player* getPlayer() = 0;
	virtual char getHealth() = 0;
	virtual bool isIndestructible() = 0;
	virtual BoardElement::Direction::DirectionType getDirection() = 0;
	virtual void draw(char x, char y) = 0;
protected:
	char id;
	BoardElement::BoardType::Type type;
};

#endif