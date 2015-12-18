#include "NetworkManager.h"
#include <QDebug>

NetworkManager::NetworkManager(Game *game, QObject *parent)
    :QObject(parent), game(game), tcpClient()
{
    connect(&tcpClient, SIGNAL(reading(QByteArray)), this, SLOT(applyFrame(QByteArray)));
    connect(&tcpClient, SIGNAL(connecting()), this, SLOT(connected()));
}

void NetworkManager::connectToHost(QHostAddress address, int port, QString name)
{
    emit game->gameStatusChanged(Game::CONNECTING);
    tcpClient.connectToHost(address, port);
    game->model1.players.resize(1);
    game->model1.players[0] = Player();
    game->model1.players[0].name = name.toLatin1();
}

void NetworkManager::connected()
{
    emit game->gameStatusChanged(Game::BEFORE_PLAYING);
    QByteArray frame(18, '\0');
    frame[0] = 1;
    frame[1] = 0;
    frame.insert(2, game->model1.players[0].name);
    frame.resize(18);
    tcpClient.write(frame);
}

void NetworkManager::disconnectFromHost()
{
    QByteArray frame(3, '\0');
    frame[0] = 3;
    frame[1] = game->player.id;
    frame[2] = 0;
    tcpClient.write(frame);
}

void NetworkManager::applyFrame(const QByteArray &frame)
{
    switch (frame[0]){
    case 1:
        if (frame[2] == 0){
            game->player.id = frame[1];
            game->isRunning = true;
            timerId = startTimer(CLIENT_SEND_INTERVAL);
            game->time.start();
            emit game->gameStatusChanged(Game::PLAYING);
        }
        break;
    case 2:
        qDebug() << "Odebrano od serwera!";
        /*game.model1 = game.model2;
        game.model2.applyFrame(frame);*/
        game->time.restart();
        break;
    case 3:
        if (frame[2] == 0){
            killTimer(timerId);
            game->isRunning = false;
            tcpClient.disconnectFromHost();
        }
    }
}

void NetworkManager::timerEvent(QTimerEvent *event)
{
    if (game->player.player_shooted || game->player.moving_direction != NONE)
    {
        qDebug() << "Sending to server";
        tcpClient.write(game->player.getFrame());
        game->player.player_shooted = false;
        game->player.moving_direction = NONE;
    }
}
