#include "ActionFrame.h"
#include <string.h>

ActionFrame::ActionFrame()
{
	ActionFrame(0,Shot::Direction::None,false);
	actionType = Frame::ActionType::Undefined;
	type = Frame::FrameType::Action;
}

ActionFrame::ActionFrame(char pId, Shot::Direction::DirectionType d, bool s)
{
	playerId = pId;
	dir = d;
	shot = s;
	actionType = Frame::ActionType::Action;
	type = Frame::FrameType::Action;
}

ActionFrame::ActionFrame(char pId, char* pN)
{
	playerId = pId;
	dir = Shot::Direction::None;
	shot = false;
	actionType = Frame::ActionType::Connect;
	type = Frame::FrameType::Action;
	strcpy(playerName,pN);
}

ActionFrame::ActionFrame(char pId)
{
	playerId = pId;
	dir = Shot::Direction::None;
	shot = false;
	actionType = Frame::ActionType::Disconnect;
	type = Frame::FrameType::Action;
}

ActionFrame::ActionFrame(char pId, Frame::ActionType::Type at)
{
	playerId = pId;
	dir = Shot::Direction::None;
	shot = false;
	actionType = at;
	type = Frame::FrameType::Action;
}