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
	Shot(int player_id, int x_start, int y_start, DIRECTION direction, int flight_periods, int power);

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
    unsigned char player_id;
    unsigned char x_start;
    unsigned char y_start;
	DIRECTION direction;
    unsigned int flight_periods;
    unsigned char power;

};

#endif
