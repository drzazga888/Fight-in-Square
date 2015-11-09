#include "Obstacle.h"

Obstacle::Obstacle(char i, char h, bool ind)
: BoardElement(i)
{
	health = h;
	indestructible = ind;
	type = BoardElement::BoardType::Obstacle;
}

void Obstacle::draw(char x, char y)
{

}