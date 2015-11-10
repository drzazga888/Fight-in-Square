#ifndef BOARD_H
#define BOARD_H

#define MAX_PLAYERS 8

#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QVector>

#include "shared/GameElements/Blank.h"
#include "shared/GameElements/Tank.h"
#include "shared/GameElements/Obstacle.h"
#include "shared/Player.h"
#include "shared/Shot.h"
#include "shared/Frames/Frame.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	Board(QWidget* parent = NULL);
	~Board();
	void hide();
	Frame::ErrorCode::Code addPlayer(int id, Player* p);
	Player* removePlayer(int id);
	Player* getPlayer(int id){ return players[id-1]; };
	virtual void paintEvent(QPaintEvent* pe);
private:
	QPainter *board;
	void pusteTlo(QPaintEvent* pe);
	bool hidden;
	QVector< QVector< BoardElement* > > elements;
	QVector<Player*> players;
	QVector<Shot*> shots;
	int plCounter;
};

#endif
