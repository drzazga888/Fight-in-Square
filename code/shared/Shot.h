#ifndef SHOT_H
#define SHOT_H

#include <QObject>

class Shot : public QObject
{
	Q_OBJECT
public:
	Shot(char x, char y, Direction d, char p);
	void setPeriods(int p);
	void addPeriods(int p);
	enum Direction {None, Up, Down, Right, Left};
private:
	char posX;
	char poxY;
	Direction dir;
	int periods;
	char power;
};

#endif