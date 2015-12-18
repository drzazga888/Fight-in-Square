#include "Server.h"

Server::Server(QObject *parent)
    :QObject(parent), isWorking(false), model(), tcpServer(), controller(model)
{
    srand(QDateTime::currentMSecsSinceEpoch());
    connect(&tcpServer, SIGNAL(reading(int, QByteArray)), this, SLOT(read(int, QByteArray)));
}

Server::~Server()
{
    switchOff();
}

void Server::log(const QString &message)
{
    emit logged(QDateTime::currentDateTime().toString() + QString(":   ") + message);
}

bool Server::switchOn(int port)
{
    if (!isWorking)
    {
        if (tcpServer.start(port))
        {
            this->port = port;
            isWorking = true;
            log(QString("Serwer został włączony, port ") + QString::number(port));
            timerId = startTimer(SERVER_SEND_INTERVAL);
            return true;
        }
        else
        {
            log(QString("Wystąpił problem z włączeniem serwera, port ") + QString::number(port));
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
    log(QString("client->server, playerId: %1, typ wiadomości: %2").arg(playerId).arg((int)message[0]));
    QByteArray response;
    switch (message[0])
    {
    case 1:
        emit playerAdded(controller.addPlayer(playerId, message.data() + 2));
        response.resize(3);
        response[0] = 1;
        response[1] = playerId;
        response[2] = 0;
        tcpServer.write(playerId, response);
        break;
    case 2:
        // muszą być przechowywane ruchy dla każdego gracza... -> klasa Movement TODO!!!
        break;
    case 3:
        controller.removePlayer(playerId);
        emit playerRemoved(playerId);
        response.resize(3);
        response[0] = 3;
        response[1] = playerId;
        response[2] = 0;
        tcpServer.write(playerId, response);
        break;
    }
}

void Server::timerEvent(QTimerEvent *event)
{
    //tcpServer.writeBroadcast(model.getFrame());
    //log("Broadcast planszy");
}
