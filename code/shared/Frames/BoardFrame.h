#ifndef BOARD_FRAME_H
#define BOARD_FRAME_H

#include <QObject>
#include <QVector>

#include "shared/GameElements/Blank.h"
#include "shared/GameElements/Tank.h"
#include "shared/GameElements/Obstacle.h"
#include "shared/Player.h"
#include "shared/Shot.h"
#include "Frame.h"

class BoardFrame : public QObject
{
	Q_OBJECT
public:
	
private:
	QVector<QVector<BoardElement*>> elements;
	QVector<Player*> players;
	QVector<Shot*> shots;
};

#endif