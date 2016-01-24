#ifndef SHOT_H
#define SHOT_H

#include "../../config.h"
#include "../Utils/Direction.h"
#include "../Frame/Frameable.h"
#include<QPoint>

/**
 * @brief
 * Informacje o wystrzelonym pocisku na planszy.
 * Obiekt takiej klasy jest "Ramkowalny"
 */
class Shot: public Frameable
{

public:

    Shot();
    Shot(int id, int player_id, int x_start, int y_start, DIRECTION direction, int flight_periods, int power);
    Shot(const QByteArray &frame);

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

    QPoint getActualShotPosition() const;

    bool operator ==( const Shot & dane) const;

    bool operator %=(  Shot & dane) const;

    /**
     * @brief id Identyfikator pocisku
     */
    unsigned char id;

    /**
     * @brief player_id Identyfikator gracza, który wystrzelił pocisk
     */
    unsigned char player_id;

    /**
     * @brief x_start Początkowa pozycja pozioma pocisku
     */
    unsigned char x_start;

    /**
     * @brief y_start Początkowa pozycja pionowa pocisku
     */
    unsigned char y_start;

    /**
     * @brief direction Kierunek, w którym leci pocisk
     */
	DIRECTION direction;

    /**
     * @brief flight_periods Liczba okresów gry, w których pocisk już leci
     */
    unsigned int flight_periods;

    /**
     * @brief power Siła pocisku
     */
    unsigned char power;

};

#endif
