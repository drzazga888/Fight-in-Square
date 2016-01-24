#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTimerEvent>
#include "../config.h"
#include "../shared/Frame/FrameApplyable.h"
#include "../shared/Utils/Direction.h"
#include "Game.h"
#include "TcpClient.h"

/**
 * @brief
 * Klasa odpowiedzialna za zarządzanie
 * klasą TcpClient i Game w ten sposób,
 * by umożliwić grę przez sieć.
 */
class NetworkManager : public QObject, public FrameApplyable
{
    Q_OBJECT

public:
    explicit NetworkManager(Game *game, QObject *parent = 0);

    /**
     * @brief
     * Metoda służąca do nawiązywania połączenia z serwerem.
     * @param address - adres IP serwera
     * @param port - port serwera
     * @param name - nazwa gracza wprowadzona w menu połączenia
     */
    void connectToHost(QHostAddress address, int port, QString name);

    /**
     * @brief
     * Metoda rozłącza klienta z serwerem
     * jeśli jest on połączony.
     */
    void disconnectFromHost();

public slots:

    /**
     * @brief
     * Odziedziczone po FrameApplyable.
     * Dzięki temu slotowi klasa potrafi przyjąć ramkę
     * i odpowiednio ją przetworzyć.
     * @param frame - ramka od serwera
     */
    virtual void applyFrame(const QByteArray &frame);

    /**
     * @brief
     * Slot na sygnał ustanowienia połączenia z serwerem.
     */
    void connected();

    /**
     * @brief
     * Slot na sygnał rozłączenia się z serwerem.
     */
    void disconnected();

private:

    /**
     * @brief
     * Funkcja, która obsługuje zdarzenie czasowe,
     * czyli wywołuje się cyklicznie.
     */
    void timerEvent(QTimerEvent *);

    /**
     * @brief game Obiekt gry
     */
    Game *game;

    /**
     * @brief tcpClient Obiekt klienta TCP
     */
    TcpClient tcpClient;

    /**
     * @brief timerId Identyfikator timer'a
     */
    int timerId;

};

#endif // NETWORKMANAGER_H
