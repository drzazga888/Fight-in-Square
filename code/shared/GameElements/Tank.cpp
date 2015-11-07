#include "Tank.h"

Tank::Tank(int p, BoardElement::Direction d)
{
	player = p;
	dir = d;
	type = BoardElement::Type::Tank;
}

void Tank::draw(char x, char y)
{

}