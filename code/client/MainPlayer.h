#ifndef MAINPLAYER_H
#define MAINPLAYER_H

#include <QVector>
#include "../shared/Frame/FrameGiveable.h"
#include "../shared/Model/Player.h"

class MainPlayer: public FrameGiveable {

public:
    MainPlayer();
    virtual ~MainPlayer() {}
    void setPlayerFromModel(QVector<Player> players);

    virtual QByteArray getFrame();

    bool player_shooted;
    DIRECTION moving_direction;
    int id;
    Player *player;

};

#endif
