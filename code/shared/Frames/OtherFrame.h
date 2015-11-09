#ifndef OTHER_FRAME_H
#define HER_FRAME_H

#include "shared/Frames/Frame.h"

class OtherFrame : public Frame
{
	Q_OBJECT
public:
	virtual Frame::FrameType::Type getType(){ return type; }
	/* metody wirtualne dla ramki akcji */
	virtual Frame::ActionType::Type getActionType(){ return Frame::ActionType::Undefined; };
	virtual Shot::Direction::DirectionType getDir(){ return Shot::Direction::None; }
	virtual bool getShot(){ return false; }
	virtual char getPlayerId(){ return 0; }
	virtual char* getPlayerName(){ return NULL; };
	/* metody wirtualne dla ramki planszy */ 
	QVector<Player*> getPlayers(){ return QVector<Player*>(); } 
	QVector<Shot*> getShots(){ return QVector<Shot*>(); }
	QVector< QVector< BoardElement* > > getElements(){ return QVector< QVector< BoardElement* > >(); }
};

#endif