#include "NetworkManager.h"
#include <QDebug>

NetworkManager::NetworkManager(Game *game, QObject *parent)
    :QObject(parent), game(game), tcpClient()
{
    connect(&tcpClient, SIGNAL(reading(QByteArray)), this, SLOT(applyFrame(QByteArray)));
    connect(&tcpClient, SIGNAL(connecting()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnecting()), this, SLOT(disconnected()));
}

void NetworkManager::connectToHost(QHostAddress address, int port, QString name)
{
    tcpClient.connectToHost(address, port);
    game->playerName = name;
    game->setStatus(Game::CONNECTING);
}

void NetworkManager::disconnectFromHost()
{
    switch (game->status)
    {
    case Game::CONNECTING:
        tcpClient.disconnectFromHost();
        game->setStatus(Game::NO_PLAYING);
        break;
    default:
        QByteArray frame(3, '\0');
        frame[0] = 3;
        frame[1] = game->player.id;
        frame[2] = 0;
        tcpClient.write(frame);
        game->setStatus(Game::SENDING_GOODBYE);
        break;
    }
}

void NetworkManager::connected()
{
    QByteArray frame(18, '\0');
    frame[0] = 1;
    frame[1] = 0;
    frame.insert(2, game->playerName.toLatin1());
    frame.resize(18);
    tcpClient.write(frame);
    game->setStatus(Game::SENDING_HELLO);
}

void NetworkManager::disconnected()
{
    game->setStatus(Game::NO_PLAYING);
}

void NetworkManager::applyFrame(const QByteArray &frame)
{
    switch (frame[0])
    {
    case 1:
        if (!frame[2])
        {
            game->player.id = frame[1];
            game->maxTime = QTime(0, 0).addSecs(*((unsigned short *)(frame.data() + 3)));
            game->gameTime = QTime(0, 0).addSecs(*((unsigned short *)(frame.data() + 5)));
            timerId = startTimer(CLIENT_SEND_INTERVAL);
            game->setStatus(Game::PLAYING);
        }
        else if (frame[2] == SERVER_IS_EMPTY)
        {
            game->player.id = frame[1];
            game->maxTime = QTime(0, 0).addSecs(*((unsigned short *)(frame.data() + 3)));
            game->gameTime = QTime(0, 0);
            game->setStatus(Game::WAITING_FOR_PLAYER);
        }
        else
            game->setErrorCode(frame[2]);
        break;
    case 2:
        if (game->status == Game::WAITING_FOR_PLAYER)
        {
            timerId = startTimer(CLIENT_SEND_INTERVAL);
            game->setStatus(Game::PLAYING);
        }
        game->applyFrame(frame);
        game->player.player_shooted = false;
        break;
    case 3:
        if (frame[2] == 0)
        {
            killTimer(timerId);
            game->setStatus(Game::DISCONNECTING);
        }
        break;
    case 4:
        killTimer(timerId);
        game->applyFrame(frame);
        game->setStatus(Game::Game::GAME_OVER);
        break;
    }
}

void NetworkManager::timerEvent(QTimerEvent *)
{
    if (game->player.player_shooted || game->player.moving_direction != NONE)
    {
        qDebug() << "Kierunek: " << game->player.moving_direction << ", strzal: " << game->player.player_shooted;
        tcpClient.write(game->player.getFrame());
    }
}
