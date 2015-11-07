#ifndef BLANK_H
#define BLANK_H

#include <QObject>
#include "BoardElement.h"

class Blank : public BoardElement
{
	Q_OBJECT
public:
	Blank(int i);
	virtual Player* getPlayer();
	virtual BoardElement::Direction getDirection() { return BoardElement::Direction::None; }
	virtual void addHealth(char h){ };
	virtual void takeHealth(char h){  };
	virtual void setDirection(BoardElement::Direction d){ };
	virtual char getHealth() { };
	virtual bool isIndestructible() { };
	virtual void draw(char x, char y);

private:

};

#endif