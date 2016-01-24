#include "PlayerAction.h"

PlayerAction::PlayerAction()
    :player_shooted(false), moving_direction(NONE), id(0)
{
}

PlayerAction::PlayerAction(int id)
    :player_shooted(false), moving_direction(NONE), id(id)
{
}

PlayerAction::PlayerAction(bool player_shooted, DIRECTION moving_direction, int id)
    :player_shooted(player_shooted), moving_direction(moving_direction), id(id)
{
}

PlayerAction::PlayerAction(QByteArray frame)
{
    applyFrame(frame);
}

QByteArray PlayerAction::getFrame() const
{
    QByteArray frame(4, '\0');
    frame[0] = 2;
    frame[1] = id;
    frame[2] = moving_direction;
    frame[3] = player_shooted;
    return frame;
}

void PlayerAction::applyFrame(const QByteArray &frame)
{
    id = frame[1];
    moving_direction = (DIRECTION)frame[2];
    if (!player_shooted)
        player_shooted = frame[3];
}
