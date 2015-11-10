#include "Player.h"
#include <string.h>

Player::Player(char i, char* n)
{
	id = i;
	strcpy(name, n);
}

Player* Player::setGroup(char g)
{
	group = g;
	return this;
}

Player* Player::setPochars(char p)
{
	pochars = p;
	return this;
}

Player* Player::addPochars(char p)
{
	pochars+=p;
	return this;
}

Player* Player::takePochars(char p)
{
	pochars-=p;
	return this;
}

Player* Player::setHealth(char h)
{
	health = h;
	return this;
}

Player* Player::addHealth(char h)
{
	health += h;
	return this;
}

Player* Player::takeHealth(char h)
{
	health -= h;
	return this;
}

Player* Player::setPower(char pw)
{
	power = pw;
	return this;
}

Player* Player::addPower(char pw)
{
	power += pw;
	return this;
}

Player* Player::takePower(char pw)
{
	power -= pw;
	return this;
}


char Player::getId()
{
	return id;
}

char Player::getGroup()
{
	return group;
}

char Player::getPochars()
{
	return pochars;
}

char Player::getHealth()
{
	return health;
}

char Player::getPower()
{
	return power;
}