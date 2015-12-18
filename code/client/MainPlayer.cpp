#include "MainPlayer.h"

MainPlayer::MainPlayer()
    :id(0), player(NULL)
{
}

void MainPlayer::setPlayerFromModel(QVector<Player> players)
{
    for (int i = 0; i < players.size(); ++i){
        if (players[i].id == id){
            player = &players[i];
            break;
        }
    }
}

QByteArray MainPlayer::getFrame()
{
    QByteArray frame(4, '\0');
    frame[0] = 2;
    frame[1] = id;
    frame[2] = moving_direction;
    frame[3] = player_shooted;
    return frame;
}
