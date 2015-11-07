#include "Obstacle.h"

Obstacle::Obstacle(i, h, ind)
{
	id = i;
	health = h;
	indestructible = ind;
	type = BoardElement::Type::Obstacle;
}

void Obstacle::draw(char x, char y)
{

}