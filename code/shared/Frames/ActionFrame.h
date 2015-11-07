#ifndef ACTION_FRAME_H
#define ACTION_FRAME_H

#include <QObject>
#include "../Shot.h"
#include "Frame.h"

class ActionFrame : public Frame
{
	Q_OBJECT
public:
	enum ActionType {Undefined, Connect, Disconnect, Action};
	ActionFrame();
	ActionFrame(int pId, Shot::Direction d, bool s);
	ActionFrame(int pId, char[64] pN);
	ActionFrame(int pId);
private:
	Shot::Direction dir;
	bool shot;
	int playerId;
	char playerName[64];
	ActionType type;
};

#endif