#ifndef BOARD_ELEMENT_H
#define BOARD_ELEMENT_H

#include <QObject>

class BoardElement : public QObject
{
	Q_OBJECT
public:
	enum Type { Blank, Tank, Obstacle };
	enum Direction {None, Up, Down, Right, Left};
	virtual int getId() { return id; }
	virtual BoardElement::Type getType(){ return type; }
	virtual void addHealth(char h) = 0;
	virtual void takeHealth(char h) = 0;
	virtual void setDirection(BoardElement::Direction d) = 0;
	virtual Player* getPlayer() = 0;
	virtual char getHealth() = 0;
	virtual bool isIndestructible() = 0;
	virtual BoardElement::Direction getDirection() = 0;
	virtual void draw(char x, char y) = 0;
protected:
	int id;
	ElementType type;
};

#endif