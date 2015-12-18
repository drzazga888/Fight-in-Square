#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <QObject>
#include <QString>
#include <QDateTime>
#include "../config.h"
#include "../shared/Model/Model.h"
#include "TcpServer.h"
#include "Controller.h"

class Server: public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();
    void log(const QString &message);
    bool switchOn(int port);
    bool switchOff();

    void timerEvent(QTimerEvent *event);

    bool isWorking;

public slots:
    void read(int playerId, const QByteArray &message);

signals:
    void logged(const QString &message);
    void playerAdded(Player &player);
    void playerRemoved(int id);

private:
    Player::GROUP assignGroup();
    Model model;
    TcpServer tcpServer;
    Controller controller;
    int timerId;
    int port;

};

#endif // SERVER_H
