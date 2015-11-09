#ifndef BLANK_H
#define BLANK_H

#include <QObject>
#include "BoardElement.h"

class Blank : public BoardElement
{
	Q_OBJECT
public:
	Blank(int i);
	virtual Player* getPlayer(){ return NULL; };
	virtual BoardElement::Direction::DirectionType getDirection() { return BoardElement::Direction::None; }
	virtual void addHealth(char h){ ++h;};
	virtual void takeHealth(char h){ ++h;};
	virtual void setDirection(BoardElement::Direction::DirectionType d){ int i = (int)d;++i; };
	virtual char getHealth() { return 0; };
	virtual bool isIndestructible() { return false; };
	virtual void draw(char x, char y);

private:

};

#endif