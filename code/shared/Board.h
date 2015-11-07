#ifndef BOARD_H
#define BOARD_H

#include <QPainter>
#include <QWidget>
#include <QPaintEvent>
#include <QVector>

#include "shared/GameElements/Blank.h"
#include "shared/GameElements/Tank.h"
#include "shared/GameElements/Obstacle.h"
#include "shared/Player.h"
#include "shared/Shot.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	Board(QWidget* parent = NULL);
	~Board();
	void hide();
	virtual void paintEvent(QPaintEvent* pe);
private:
	QPainter *board;
	void pusteTlo(QPaintEvent* pe);
	bool hidden;
	QVector<QVector<BoardElement*>> elements;
	QVector<Player*> players;
	QVector<Shot*> shots;
};

#endif
