#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "../../config.h"
#include "../../shared/Utils/Direction.h"
#include "../Frame/Frameable.h"

/**
 * @brief
 * Obiekt reprezentuje gracza
 * jak i czołg, który należy do tego gracza.
 * Zawiera jedynie informacje potrzebne do
 * odtworzenia sytuacji na planszy - informacje
 * o akcjach, które są podejmowane przez gracza
 * zawarte są w PlayerAction
 */
class Player: public Frameable
{

public:

    /**
     * @brief grupa (drużyna), do której gracz może przynależeć
     */
	enum GROUP {
        RED_GROUP = 0,
        BLUE_GROUP = 1
	};

    Player();
    Player(int id, GROUP group, int x, int y, DIRECTION direction, QByteArray name);
    Player(int id, Player::GROUP group, int points, int health, int power, int x, int y, DIRECTION direction, QByteArray name, bool is_alive, int death_time);
    Player(QByteArray frame);

    /**
     * @brief applyFrame przyjmuje ramkę i ją aplikuje na obiekt
     * @param frame - ramka
     */
    virtual void applyFrame(const QByteArray &frame);

    /**
     * @brief getFrame tworzy ramkę z obiektu
     * @return ramka
     */
    virtual QByteArray getFrame() const;

    /**
     * @brief id Identyfikator gracza
     */
    unsigned char id;

    /**
     * @brief group Grupa, do której należy gracz
     */
    GROUP group;

    /**
     * @brief points Liczba punktów
     */
    unsigned char points;

    /**
     * @brief health Zdrowie
     */
    unsigned char health;

    /**
     * @brief power Moc pocisków, które gracz w tym momencie wystrzeliwuje
     */
    unsigned char power;

    /**
     * @brief x Pozycja pozioma gracza
     */
    unsigned char x;

    /**
     * @brief y Pozycja pionowa gracza
     */
    unsigned char y;

    /**
     * @brief direction Kierunek, w którym jest ustawiony gracz
     */
	DIRECTION direction;

    /**
     * @brief name Nazwa gracza
     */
    QByteArray name;

    /**
     * @brief is_alive Flaga informująca, czy gracz w danym mmencie żyje
     */
    bool is_alive;

    /**
     * @brief death_time
     */
    unsigned char death_time;

};

#endif
