#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QVector>
#include "shared/Player.h"
#include "shared/Shot.h"
#include "shared/GameElements/BoardElement.h"

class Frame : public QObject
{
	Q_OBJECT
public:
	class FrameType
	{
	public:
		enum Type {Action, Board, Other};
	};
	class ActionType
	{
	public:
		enum Type {Undefined, Connect, Disconnect, Action};
	};
	class ErrorCode
	{
	public:
		enum Code {Undefined, MaxPlayers};
	};
	Frame(){ errorCode = Frame::ErrorCode::Undefined; }
	virtual Frame::FrameType::Type getType(){ return type; }
	virtual Frame::ErrorCode::Code getErrorCode(){ return errorCode; }
	virtual void setErrorCode(Frame::ErrorCode::Code ec){ errorCode = ec; }
	/* metody wirtualne dla ramki akcji */
	virtual Frame::ActionType::Type getActionType() = 0;
	virtual Shot::Direction::DirectionType getDir() = 0;
	virtual bool getShot() = 0;
	virtual char getPlayerId() = 0;
	virtual char* getPlayerName() = 0;
	/* metody wirtualne dla ramki planszy */ 
	virtual QVector<Player*> getPlayers() = 0;
	virtual QVector<Shot*> getShots() = 0;
	virtual QVector< QVector< BoardElement* > > getElements() = 0;
protected:
	Frame::FrameType::Type type;
	Frame::ErrorCode::Code errorCode;
};

#endif