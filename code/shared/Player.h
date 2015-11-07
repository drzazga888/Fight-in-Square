#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
	Q_OBJECT
public:
	Player(char i, const char* n);
	Player* setGroup(char g);
	Player* setPochars(char p);
	Player* addPochars(char p);
	Player* takePochars(char p);
	Player* setHealth(char h);
	Player* addHealth(char h);
	Player* takeHealth(char h);
	Player* setPower(char pw);
	Player* addPower(char pw);
	Player* takePower(char pw);

	char getId();
	char getGroup();
	char getPochars();
	char getHealth();
	char getPower();
	const char* getName();
private:
	char id;
	char group;
	char pochars;
	char health;
	char power;
	char name[64];
};

#endif