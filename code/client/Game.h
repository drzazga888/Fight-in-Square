#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTime>
#include "../config.h"
#include "../shared/Utils/Direction.h"
#include "MainPlayer.h"
#include "shared/Model/Model.h"

class Game: public QObject
{
    Q_OBJECT

public:

    enum STATUS {
        MENU,
        CONNECTING,
        BEFORE_PLAYING,
        PLAYING
    };

    Game();
    void handleKeyboard(int key);
    float getPhaseOverlay();

    bool isRunning;
    Model model1, model2;
    MainPlayer player;
    QTime time;

signals:
    void gameStatusChanged(Game::STATUS gameStatus);

};

#endif
