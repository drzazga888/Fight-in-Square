#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "../shared/Utils/Direction.h"
#include "../shared/Frame/Frameable.h"

/**
 * @brief
 * Klasa przechowuje akcje gracza, czyli:
 * - kierunek, w którym gracz chce się ruszyć
 *   (bądź brak poruszenia)
 * - pole, które stwierdza, czy pocisk został wystrzelony
 * PlayerAction powiązany z klasą Player poprzez pole id.
 */
class PlayerAction: public Frameable
{

public:
    PlayerAction();
    PlayerAction(int id);
    PlayerAction(bool player_shooted, DIRECTION moving_direction, int id);
    PlayerAction(QByteArray frame);
    virtual ~PlayerAction() {}

    /**
     * @brief applyFrame przyjmuje ramkę i ją aplikuje na obiekt
     * @param frame - ramka
     */
    virtual QByteArray getFrame() const;

    /**
     * @brief getFrame tworzy ramkę z obiektu
     * @return ramka
     */
    virtual void applyFrame(const QByteArray &frame);

    bool player_shooted;
    DIRECTION moving_direction;
    int id;

};

#endif // PLAYERACTION_H
