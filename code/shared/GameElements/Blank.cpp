#include "Blank.h"

Blank::Blank(int i)
: BoardElement(i)
{
	type = BoardElement::BoardType::Blank;
}

void Blank::draw(char x, char y)
{
	++x;++y;
}
