#ifndef ACTION_FRAME_H
#define ACTION_FRAME_H

#include <QObject>
#include "../Shot.h"
#include "Frame.h"

class ActionFrame : public Frame
{
	Q_OBJECT
public:
	ActionFrame();
	ActionFrame(char pId, Shot::Direction::DirectionType d, bool s);
	ActionFrame(char pId, char* pN);
	ActionFrame(char pId);
	ActionFrame(char pId, Frame::ActionType::Type at);
	/* metody wirtualne dla ramki akcji */
	virtual Frame::ActionType::Type getActionType(){ return actionType; };
	virtual Shot::Direction::DirectionType getDir(){ return dir; }
	virtual bool getShot(){ return shot; }
	virtual char getPlayerId(){ return playerId; }
	virtual char* getPlayerName(){ return playerName; }
	/* metody wirtualne dla ramki planszy */ 
	QVector<Player*> getPlayers(){ return QVector<Player*>(); } 
	QVector<Shot*> getShots(){ return QVector<Shot*>(); }
	QVector< QVector< BoardElement* > > getElements(){ return QVector< QVector< BoardElement* > >(); }
private:
	Shot::Direction::DirectionType dir;
	bool shot;
	char playerId;
	char playerName[64];
	Frame::ActionType::Type actionType;
};

#endif