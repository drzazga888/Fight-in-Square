#include "Frame.h"

ActionFrame::ActionFrame()
: ActionFrame(0,Shot::Direction::None,false)
{
	type = ActionType::Undefined;
}

ActionFrame::ActionFrame(int pId, Shot::Direction d, bool s)
{
	playerId = pId;
	dir = d;
	shot = s;
	type = ActionType::Action;
}

ActionFrame(int pId, char[64] pN)
{
	playerId = pId;
	dir = Shot::Direction::None;
	shot = false;
	type = ActionType::Connect;
}

ActionFrame(int pId)
{
	playerId = pId;
	dir = Shot::Direction::None;
	shot = false;
	type = ActionType::Disconnect;
}