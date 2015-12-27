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

    unsigned char id;
    GROUP group;
    unsigned char points;
    unsigned char health;
    unsigned char power;
    unsigned char x;
    unsigned char y;
	DIRECTION direction;
    QByteArray name;
    bool is_alive;
    unsigned char death_time;

};

#endif
