#ifndef SHOT_H
#define SHOT_H

#include <QObject>

class Shot : public QObject
{
	Q_OBJECT
public:
	class Direction
	{
	public:
		enum DirectionType {None, Up, Down, Right, Left};
	};
	Shot(char x, char y, Shot::Direction::DirectionType d, char p);
	void setPeriods(int p);
	void addPeriods(int p);
private:
	char posX;
	char posY;
	Shot::Direction::DirectionType dir;
	int periods;
	char power;
};

#endif