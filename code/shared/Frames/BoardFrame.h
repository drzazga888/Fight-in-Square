#ifndef BOARD_FRAME_H
#define BOARD_FRAME_H

#include <QObject>
#include <QVector>

#include "shared/GameElements/Blank.h"
#include "shared/GameElements/Tank.h"
#include "shared/GameElements/Obstacle.h"
#include "Frame.h"

class BoardFrame : public Frame
{
	Q_OBJECT
public:
	BoardFrame();
	/* metody wirtualne dla ramki akcji */
	virtual Frame::ActionType::Type getActionType(){ return Frame::ActionType::Undefined; };
	virtual Shot::Direction::DirectionType getDir(){ return Shot::Direction::None; }
	virtual bool getShot(){ return false; }
	virtual char getPlayerId(){ return 0; }
	virtual char* getPlayerName(){ return NULL; };
	/* metody wirtualne dla ramki planszy */ 
	virtual QVector<Player*> getPlayers(){ return players; } 
	virtual QVector<Shot*> getShots(){ return shots; }
	virtual QVector< QVector< BoardElement* > > getElements(){ return elements; }
private:
	QVector< QVector< BoardElement* > > elements;
	QVector<Player*> players;
	QVector<Shot*> shots;
};

#endif