#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTimerEvent>
#include "../config.h"
#include "../shared/Frame/FrameApplyable.h"
#include "Game.h"
#include "TcpClient.h"

class NetworkManager : public QObject, public FrameApplyable
{
    Q_OBJECT
public:
    explicit NetworkManager(Game *game, QObject *parent = 0);
    void connectToHost(QHostAddress address, int port, QString name);
    void disconnectFromHost();

public slots:
    virtual void applyFrame(const QByteArray &frame);
    void connected();

private:
    void timerEvent(QTimerEvent *event);

    Game *game;
    TcpClient tcpClient;
    int timerId;

};

#endif // NETWORKMANAGER_H
