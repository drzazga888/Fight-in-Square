#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include "../../config.h"
#include "../Frame/Frameable.h"
#include "Board.h"
#include "Player.h"
#include "Shot.h"

/**
 * @brief
 * Model zawiera wszystkie informacje
 * potrzebne do odtworzenia planszy
 * i wszystkiego, co się na niej znajduje
 * (czyli pocisków i czołgów).
 */
class Model : public Frameable
{

public:
    Model();
    virtual ~Model() {}

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
     * @brief board Obiekt planszy, na któryj toczy się rozgrywka
     */
    Board board;

    /**
     * @brief players Zbiór wszystkich graczy, uczestniczacych w grze
     */
    QMap<int, Player> players;

    /**
     * @brief shots Zbiór wszystkich pocisków, które aktualnie są na planszy
     */
    QMap<int, Shot> shots;
};

#endif // MODEL_H
