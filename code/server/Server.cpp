#include "Server.h"

Server::Server(Data &data, QObject *parent)
    :QObject(parent), isWorking(false), data(data), tcpServer(), controller(data)
{
    srand(QDateTime::currentMSecsSinceEpoch());
    connect(&tcpServer, SIGNAL(reading(int, QByteArray)), this, SLOT(read(int, QByteArray)));
    connect(&tcpServer, SIGNAL(disconnecting(int)), this, SLOT(disconnected(int)));
}

Server::~Server()
{
    switchOff();
}

void Server::log(const QString &message)
{
    emit logged(QString("%1:   %2").arg(QDateTime::currentDateTime().toString()).arg(message));
}

bool Server::switchOn(int port, const QTime &maxTime)
{
    if (!isWorking)
    {
        if (tcpServer.start(port))
        {
            isTimerRunning = false;
            this->port = port;
            this->maxTime = maxTime;
            isWorking = true;
            log(QString("Serwer został włączony, port %1").arg(port));
            return true;
        }
        else
        {
            log(QString("Wystąpił problem z włączeniem serwera, port %1").arg(port));
            return false;
        }
    }
    return false;
}

bool Server::switchOff()
{
    if (isWorking)
    {
        if (tcpServer.stop())
        {
            if (isTimerRunning)
                killTimer(timerId);
            log("Serwer został wyłączony");
            isWorking = false;
            return true;
        }
        else
        {
            log("Wystąpił problem z wyłączeniem serwera");
            return false;
        }
    }
    return false;
}

void Server::read(int playerId, const QByteArray &message)
{
/*LUKI*/    //qDebug() << ((gameTime.elapsed() / 1000) >> 8) << ", " << gameTime.elapsed() / 1000;
    log(QString("Otrzymano ramkę, playerId: %1, typ: %2").arg(playerId).arg((int)message[0]));
    QByteArray response;
    switch (message[0])
    {
    case 1:
        if (!isNameUnique(QByteArray(message.data() + 2, 16)))
        {
            response.resize(3);
            response[0] = 1;
            response[1] = playerId;
            response[2] = USER_NAME_IS_NOT_UNIQUE;
            tcpServer.write(playerId, response);
            tcpServer.disconnect(playerId);
        }
        else if (data.model.players.size() == MAX_PLAYERS)
        {
            response.resize(3);
            response[0] = 1;
            response[1] = playerId;
            response[2] = SERVER_IS_FULL;
            tcpServer.write(playerId, response);
            tcpServer.disconnect(playerId);
        }
        else if (data.model.players.isEmpty())
        {
            emit playerAdded(controller.addPlayer(playerId, message.data() + 2));
            response.resize(5);
            response[0] = 1;
            response[1] = playerId;
            response[2] = SERVER_IS_EMPTY;
            tcpServer.write(playerId, response);
        }
        else {
            startPlaying();
            emit playerAdded(controller.addPlayer(playerId, message.data() + 2));
            response.resize(5);
            response[0] = 1;
            response[1] = playerId;
            response[2] = 0;
            response[3] = gameTime.elapsed() / 1000;
            response[4] = (gameTime.elapsed() / 1000) >> 8;
            tcpServer.write(playerId, response);
        }
        break;
    case 2:
        data.playerActions[playerId].applyFrame(message);
        break;
    case 3:
        response.resize(3);
        response[0] = 3;
        response[1] = playerId;
        response[2] = 0;
        tcpServer.write(playerId, response);
        tcpServer.disconnect(playerId);
        break;
    }
}

void Server::startPlaying()
{
    if (!isTimerRunning)
    {
        isTimerRunning = true;
        gameTime.start();
        timerId = startTimer(SERVER_SEND_INTERVAL);
    }
}

void Server::disconnected(int playerId)
{
    log(QString("Rozłączenie gracza, playerId: %1").arg(playerId));
    controller.removePlayer(playerId);
    emit playerRemoved(playerId);
}

void Server::timerEvent(QTimerEvent *)
{
    if (isTimerRunning)
    {
        if (QTime(0, 0).addMSecs(gameTime.elapsed()) >= maxTime)
        {
            // obsługa końca gry
            emit serverClosed();
        }
        controller.nextModelStatus();
        if (data.model.players.size())
        {
            tcpServer.writeBroadcast(data.model.getFrame());
            log(QStringLiteral("Broadcast planszy"));
        }
    }
}

void Server::refreshController()
{
    mapFromFile.loadIDMapFromFile();
    controller.clearModelFromDataObject();
    controller.loadExtendedBoard(mapFromFile.getIdBoard());
}

void Server::setPathExtendedMap(QString &load)
{
    mapFromFile.SetFilePathName(load);
}

bool Server::isNameUnique(QString name)
{
    foreach (const Player &player, data.model.players) {
        if (QString::fromLatin1(player.name) == name)
            return false;
    }
    qDebug() << "Unikalne!";
    return true;
}
