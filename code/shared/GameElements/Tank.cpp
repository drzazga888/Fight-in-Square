#include "Tank.h"

Tank::Tank(Player* p, BoardElement::Direction::DirectionType d)
: BoardElement(0)
{
	player = p;
	dir = d;
	type = BoardElement::BoardType::Tank;
}

void Tank::draw(char x, char y)
{

}