#include "Shot.h"

Shot::Shot(char x, char y, Direction d, char p)
{
	posX = x;
	posY = y;
	dir = d;
	power = p;
	periods = 0;
}

void Shot::setPeriods(int p)
{
	periods = p;
}

void Shot::addPeriods(int p)
{
	periods += p;
}